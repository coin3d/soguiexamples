/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/manips/SoClipPlaneManip.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include "Cute/SoQtColorTableEditor.h"

#include <SmallChange/nodekits/LegendKit.h>
#include <SmallChange/nodes/ViewportRegion.h>
#include <SmallChange/misc/Init.h>

#include <VolumeViz/nodes/SoVolumeRendering.h>
#include <VolumeViz/nodes/SoVolumeData.h>
#include <VolumeViz/nodes/SoTransferFunction.h>
#include <VolumeViz/nodes/SoVolumeRender.h>

#include <cassert>

// *************************************************************************

// Some global variables and pointers
static uint8_t * colors = NULL; 
static LegendKit * curvekit = NULL;
static SoQtColorTableEditor * colortableedit = NULL;
static const char * MANIPSWITCH = "manipswitch";
SoVolumeRender * volrender;
SoTransferFunction * voltransfunc;

// *************************************************************************

// Callback for the legendkit connected to the colortable editor
static uint32_t 
curvekitCallback(double t)
{  
  int num = colortableedit->getMode(); // getMode() also returns the number of colors
  int ix = int(t * 256.0 + 0.5);
  uint32_t color = 0;
  // set rgb
  for (int i = 0; i < 3; i++) {
    int j = (num > 2) ? i : 0;
    color |= colors[ix * num + j] << (3-i)*8;
  }
  // if num == 2 || num == 4, set alpha
  color |= (num % 2) ? 255 : colors[ix*num + (num-1)];
  return color;
}

// *************************************************************************

// Callback for the colortableeditor
static void
colorTableCallback(SoQtColorTableEditor * editor, void * userData)
{
  editor->getColors(colors, 256);
    
  // This is done to force an unscheduled redraw of the legende kit.
  curvekit->setDiscreteMode(TRUE);
  curvekit->setDiscreteMode(FALSE);
    
  voltransfunc->predefColorMap.setValue(SoTransferFunction::NONE);
  voltransfunc->colorMapType.setValue(SoTransferFunction::RGBA);
  
  for (int i=0;i<256*4;++i) {
    voltransfunc->colorMap.set1Value(i, colors[i]/256.0f);   
  }

  voltransfunc->reMap(1, 65535);
}

// *************************************************************************

// Keyboard callback method
static void
event_cb(void * userdata, SoEventCallback * node)
{
  if (SO_KEY_PRESS_EVENT(node->getEvent(), C)) { // 'c' = Clipplane on/off
    SoSwitch * manipswitch = (SoSwitch *)
      SoBase::getNamedBase(MANIPSWITCH, SoSwitch::getClassTypeId());
    assert(manipswitch);
    const int val = manipswitch->whichChild.getValue();
    manipswitch->whichChild = (val == SO_SWITCH_NONE) ? SO_SWITCH_ALL : SO_SWITCH_NONE;
  }
  else if (SO_KEY_PRESS_EVENT(node->getEvent(), M)) { // 'm' = max intensity
    if (volrender->composition.getValue() != SoVolumeRender::MAX_INTENSITY)
      volrender->composition.setValue(SoVolumeRender::MAX_INTENSITY);
    else
      volrender->composition.setValue(SoVolumeRender::ALPHA_BLENDING);
  }
  else if (SO_KEY_PRESS_EVENT(node->getEvent(), S)) { // 's' = sum intensity
    if (volrender->composition.getValue() != SoVolumeRender::SUM_INTENSITY)
      volrender->composition.setValue(SoVolumeRender::SUM_INTENSITY);
    else
      volrender->composition.setValue(SoVolumeRender::ALPHA_BLENDING);
  } 
  else if (SO_KEY_PRESS_EVENT(node->getEvent(), I)) { // 'i' = Interpolation toggle
    if (volrender->interpolation.getValue() == SoVolumeRender::LINEAR)
      volrender->interpolation.setValue(SoVolumeRender::NEAREST);
    else 
      volrender->interpolation.setValue(SoVolumeRender::LINEAR);
  }
}

// *************************************************************************

// A method for setting up a nice-looking legend kit
static LegendKit * 
newLegendKit(const SbVec2s & pos) 
{
  LegendKit * kit = new LegendKit; 
  kit->setImageTransparency(0.2f);
  kit->useTextureNotImage(TRUE);
  kit->setBackgroundColor(SbColor(1.0f, 1.0f, 1.0f), 0.8f);
  kit->setTickAndLinesColor(SbColor(1.0f, 1.0f, 1.0f), 0.5f);
  kit->setPosition(pos);
  kit->topSpace = 10.0f;
  kit->setDiscreteMode(FALSE);  
  return kit;
}

// *************************************************************************

// Entry point
int
main(int argc, char ** argv)
{
  QWidget * window = SoQt::init(argv[0]);

  // Initialize SmallChange and SIMVoleon.
  smallchange_init();
  SoVolumeRendering::init();
  
  if (argc < 2) { 
    printf("Usage: $ %s file [complexity]\n", argv[0]);
    exit(0);
  }
    
  // Print user instructions.
  printf("\n");
  printf("Manipulate the colour-channels to change appearance of the rendered volume data.\n\n");
  printf(" 'c' - Activate clip plane.\n");
  printf(" 'm' - Max intensity rendering.\n");
  printf(" 's' - Sum intensity rendering.\n");
  printf(" 'i' - Toggle texture interpolation (LINEAR/NEAREST).\n\n\n");

  // Create a viewer with a blue tinted background and a stereo offset
  // of 200.0f.
  SoQtExaminerViewer * examinerviewer = new SoQtExaminerViewer(window);
  examinerviewer->setBackgroundColor(SbColor(0.176f, 0.234f, 0.477f));
  examinerviewer->setTransparencyType(SoGLRenderAction::BLEND); 
  examinerviewer->setStereoOffset(200.0f);	

  // Setup a colortable which shall be used as transfer function for
  // the volume rendering.
  colortableedit = new SoQtColorTableEditor;
  colortableedit->setMode(SoQtColorTableEditor::RGBA);
  colors = new uint8_t[256*colortableedit->getMode()];

  colortableedit->getColors(colors, 256);
  for (unsigned int i=0; i < 256; i++) { colors[i*4+3] = i; }
  colortableedit->setColors(colors, 256);

  // Create a root separator and a separator for the volume-render
  // nodes.
  SoSeparator * root = new SoSeparator;
  SoSeparator * volsep = new SoSeparator;
  assert(root);
  root->ref();

  // Create an event callback which catches keypresses.
  SoEventCallback * event = new SoEventCallback;
  root->addChild(event);
  event->addEventCallback(SoKeyboardEvent::getClassTypeId(), event_cb, NULL);

  // Create volume data node and set filename.
  SoVolumeData * voldat = new SoVolumeData;  
  voldat->fileName.setValue(argv[1]);

  // Create transfer function node.
  voltransfunc = new SoTransferFunction();

  // Create the volume render node which do the actual rendering.
  volrender = new SoVolumeRender;

  // Parse the complexity value if present.

  if (argc > 2) {
    float complexity = atof(argv[2]);
    if (complexity > 0) {
      SoComplexity * voldetails = new SoComplexity;      
      complexity = (complexity > 1.0f) ? 1.0f : complexity;
      voldetails->value.setValue(complexity);
      volsep->addChild(voldetails);
    } else {
      printf("[ Warning: Failed to parse complexity value. Valid "
             "range is '0.1' to '1.0']\n");
    }
  }

  // Use a SoSwitch node above the clip plane manipulator to make it easy
  // to activate and deactivate.
  SoSwitch * manipswitch = new SoSwitch;
  manipswitch->whichChild = SO_SWITCH_NONE;
  manipswitch->setName(MANIPSWITCH); // Name it so we can easily grab it.
  SoClipPlaneManip * clipplane = new SoClipPlaneManip;
  manipswitch->addChild(clipplane);
 
  // Make sure the legend kits and editors are initialized
  // before attaching callbacks.
  curvekit = newLegendKit(SbVec2s(20, 20));
  curvekit->description.setValue("RGB");
  colortableedit->setChangeCallback(colorTableCallback, colortableedit);
  curvekit->setColorCB(curvekitCallback);

  // Build complete scenegraph.
  volsep->addChild(manipswitch);
  volsep->addChild(voldat);
  volsep->addChild(voltransfunc);
  volsep->addChild(volrender);
  root->addChild(volsep);
  root->addChild(curvekit);

  // Setup the clipplane last, as its size must be adjusted according
  // to the scenegraph bounding box.
  SoGetBoundingBoxAction ba(examinerviewer->getViewportRegion());
  ba.apply(root);  
  SbBox3f box = ba.getBoundingBox();
  clipplane->setValue(box, SbVec3f(1.0f, 0, 0), 1.0f);
  
  // Add scenegraph to viewer.
  examinerviewer->setSceneGraph(root);
  examinerviewer->show();
  SoQt::show(window);
  
  // Activate colortable editor widget.
  colortableedit->show();

  // Start app.
  SoQt::mainLoop();

  // Clean up before exiting.
  delete examinerviewer;
  root->unref();

  return 0;
}

