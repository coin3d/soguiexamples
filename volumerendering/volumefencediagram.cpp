/**************************************************************************\
 *
 *  This file is part of a set of example programs for the Coin library.
 *  Copyright (C) 2000-2003 by Systems in Motion. All rights reserved.
 *
 *                   <URL:http://www.coin3d.org>
 *
 *  This sourcecode can be redistributed and/or modified under the
 *  terms of the GNU General Public License version 2 as published by
 *  the Free Software Foundation. See the file COPYING at the root
 *  directory of the distribution for more details.
 *
 *  As a special exception, all sourcecode of the demo examples can be
 *  used for any purpose for licensees of the Coin Professional
 *  Edition License, without the restrictions of the GNU GPL. See our
 *  web pages for information about how to acquire a Professional Edition
 *  License.
 *
 *  Systems in Motion, <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/draggers/SoDragPointDragger.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/nodes/SoScale.h>

#include <VolumeViz/nodes/SoOrthoSlice.h>
#include <VolumeViz/nodes/SoVolumeData.h>
#include <VolumeViz/nodes/SoVolumeRender.h>
#include <VolumeViz/nodes/SoTransferFunction.h>
#include <VolumeViz/nodes/SoVolumeFaceSet.h>
#include <VolumeViz/nodes/SoVolumeTriangleStripSet.h>

// *************************************************************************

#define VOLUMESIZE_X 64
#define VOLUMESIZE_Y 64
#define VOLUMESIZE_Z 64

SbVec3f manipscalefactor(0.1f, 0.1f, 0.1f); // ManipDragger scaling size 
int fence_segments = 4; // Default number of fence segments
SoFieldSensor * fieldsensor = NULL;
SoDragPointDragger ** draggerlist = NULL;
SoCoordinate3 * fencecoords = NULL;
int currentfencetransfcolour = 1;
int currentwalltransfcolour = 4;
SoTransferFunction * fencetransfunction = NULL;
SoTransferFunction * walltransfunction = NULL;

const int fencetransftable[] = {
  SoTransferFunction::GRAY, SoTransferFunction::TEMPERATURE, SoTransferFunction::PHYSICS,
  SoTransferFunction::STANDARD, SoTransferFunction::GLOW, SoTransferFunction::BLUE_RED,
  SoTransferFunction::SEISMIC
};
const int fencetransftablelen = sizeof(fencetransftable)/sizeof(int);

// *************************************************************************

// Generate a plasma 3D texture
unsigned char * generateTexture(SbVec3s & dim)
{
  int val;
  float x,y,z;
  unsigned char pixval;
  unsigned char * bitmap = new unsigned char[dim[0] * dim[1] * dim[2]];

  (void)fprintf(stdout, "Generating [%dx%dx%d] ", dim[0], dim[1], dim[2]);
  for (int k = 0;k<dim[2];k++) {
    (void)fprintf(stdout, "."); fflush(stdout);
    z = k*360/dim[2];
    for (int j = 0;j<dim[1];j++) {
      y = (j-dim[1]/2)/2;
      for (int i = 0;i<dim[0];i++) {
        x = (i-dim[1]/2)/2;
        val = int(x*x + y*y*sin(2*x*M_PI/dim[1] + z*M_PI/180));
        val = abs(val%512);
        if (val >= 256) val = 511-val;
        bitmap[k*dim[0]*dim[1] + j*dim[1] + i] = val;
      }
    }
  }

  (void)fprintf(stdout, "\n"); fflush(stdout);
  
  return bitmap;
}

// *************************************************************************

// Keyboard callback method
void keyboardCB(void * userdata, SoEventCallback * node)
{
  
  if (SO_KEY_PRESS_EVENT(node->getEvent(), Q)) { 
    currentfencetransfcolour++;    
    if (currentfencetransfcolour >= fencetransftablelen) currentfencetransfcolour = 0;
  }
  else if (SO_KEY_PRESS_EVENT(node->getEvent(), W)) { 
    currentfencetransfcolour--; 
    if (currentfencetransfcolour < 0) currentfencetransfcolour = fencetransftablelen-1;
  }

  if (SO_KEY_PRESS_EVENT(node->getEvent(), E)) { 
    currentwalltransfcolour++;    
    if (currentwalltransfcolour >= fencetransftablelen) currentwalltransfcolour = 0;
  }
  else if (SO_KEY_PRESS_EVENT(node->getEvent(), R)) { 
    currentwalltransfcolour--; 
    if (currentwalltransfcolour < 0) currentwalltransfcolour = fencetransftablelen-1;
  }

  // Update transfer functions
  fencetransfunction->predefColorMap.setValue(fencetransftable[currentfencetransfcolour]);
  walltransfunction->predefColorMap.setValue(fencetransftable[currentwalltransfcolour]);
  
}

// *************************************************************************

// Callback for the point draggers.
void draggerCB(void * data, SoSensor * sensor)
{
  for (int i=0;i<=fence_segments;++i) {    
    SbVec3f trans = draggerlist[i]->translation.getValue();
    trans[0] *= manipscalefactor[0]; // Scale down translations
    trans[1] *= manipscalefactor[1];
    trans[2] *= manipscalefactor[2];
    SbVec3f original = fencecoords->point[i*2];    
    fencecoords->point.set1Value(i*2, SbVec3f(trans[0], original[1], trans[2])); 
    fencecoords->point.set1Value(i*2 + 1, trans);
  }
}

// *************************************************************************

// Build a semi-random 'fence' 
SoSeparator * buildFaceSet(SbVec3f & dim)
{
  SoSeparator * root = new SoSeparator;
  fencecoords = new SoCoordinate3;
  
  for (int i=0;i<(fence_segments + 1);i++) {
    float yrand = (dim[1] / 2)  - (((float) rand()) / RAND_MAX) * (dim[1] / 3.0f);
    float zrand = (dim[2] / 4) - (((float) rand()) / RAND_MAX) * (dim[2] / 4.0f);  
    fencecoords->point.set1Value(i * 2, 
                                 (-dim[0] / 2) + (i * (dim[0]/fence_segments)),
                                 (-dim[1] / 2),
                                 zrand);
    fencecoords->point.set1Value((i * 2) + 1, 
                                 (-dim[0] / 2) + (i * (dim[0]/fence_segments)),
                                 (-dim[1] / 4) + yrand,
                                 zrand);
  }

  fencetransfunction = new SoTransferFunction;
  fencetransfunction->predefColorMap.setValue(SoTransferFunction::TEMPERATURE);

  SoVolumeTriangleStripSet * volfaceset = new SoVolumeTriangleStripSet;
  volfaceset->numVertices.set1Value(0, (fence_segments * 2) + 2);
  volfaceset->clipGeometry.setValue(TRUE);

  root->addChild(fencetransfunction);
  root->addChild(fencecoords);
  root->addChild(volfaceset);

  return root;  
}

// *************************************************************************

// Create the point draggers. Connect them to upper vertices of the
// fence.
SoSeparator * createManips()
{
  SoSeparator * root = new SoSeparator;
  SoScale * manipscale = new SoScale;
  manipscale->scaleFactor.setValue(manipscalefactor);
  root->addChild(manipscale); // Scale up dragger size

  draggerlist = new SoDragPointDragger*[fence_segments];
     
  for (int i=0;i<=fence_segments;++i) {

    draggerlist[i] = new SoDragPointDragger;
    SbVec3f transval(fencecoords->point[(2 * i) + 1][0] / manipscalefactor[0],
                     fencecoords->point[(2 * i) + 1][1] / manipscalefactor[1],
                     fencecoords->point[(2 * i) + 1][2] / manipscalefactor[2]);                     
    draggerlist[i]->translation.setValue(transval);
    fieldsensor = new SoFieldSensor(draggerCB, NULL);
    fieldsensor->attach(&draggerlist[i]->translation);
  
    root->addChild(draggerlist[i]);
  }

  return root;
}

// *************************************************************************

int main(int argc, char * argv[])
{
  QWidget * window = SoQt::init(argv[0]);
  if (window == NULL) exit(1);
  SoVolumeRendering::init();

  printf("Volume FaceSet demonstration.\n"
         " Usage: $ %s [volfile [nr. of fence-segments]]\n", argv[0]);
 
  // Create root separator
  SoSeparator * root = new SoSeparator;
  root->ref();

  // Setup data to visualize
  SbVec3s dim(VOLUMESIZE_X, VOLUMESIZE_Y, VOLUMESIZE_Z); 
  SoVolumeData * voldata = new SoVolumeData();  
  unsigned char * voltexture = NULL;

  if (argc < 2) { // Filename specified?
    printf("No volume data set specified. Generating a 3D plasma texture.\n");
    voltexture = generateTexture(dim);
    voldata->setVolumeData(dim, voltexture, SoVolumeData::UNSIGNED_BYTE);
  }
  else {
    voldata->fileName.setValue(argv[1]);
  }
 
  if (argc >= 3) { // Number of segments specified?
    int temp = atoi(argv[2]);
    if (temp > 3) fence_segments = temp;
    else printf("NOTE: Specified number of segments must be > 3.\n");     
  }


  // Fetch the volume dimensions (incase we loaded a VOL file)  
  SbBox3f volbox = voldata->getVolumeSize();
  SbVec3f volsize;
  volbox.getSize(volsize[0], volsize[1], volsize[2]);
  
  // Colour scheme for the walls
  walltransfunction = new SoTransferFunction;
  walltransfunction->predefColorMap.setValue(SoTransferFunction::GLOW);
  
  // Init the rear 'walls' of the scene.
  SoOrthoSlice * backwall = new SoOrthoSlice;
  backwall->sliceNumber.setValue(0);
  backwall->axis.setValue(SoOrthoSlice::Z);
  SoOrthoSlice * floor = new SoOrthoSlice;
  floor->sliceNumber.setValue(0);
  floor->axis.setValue(SoOrthoSlice::Y);
  SoOrthoSlice * leftwall = new SoOrthoSlice;
  leftwall->sliceNumber.setValue(0);
  leftwall->axis.setValue(SoOrthoSlice::X);

  // Add data + transfer function
  root->addChild(voldata);
  root->addChild(walltransfunction);

  // Add walls
  root->addChild(backwall);
  root->addChild(leftwall);
  root->addChild(floor);

  // Add fence
  SoSeparator * volfacesetroot = buildFaceSet(volsize);
  root->addChild(volfacesetroot);

  // Add manipulators
  SoSeparator * manips = createManips();
  root->addChild(manips);


  // Setup renderarea
  SoQtExaminerViewer * renderarea = new SoQtExaminerViewer(window);
  renderarea->setSceneGraph(root);
  renderarea->setBackgroundColor(SbColor(0.176, 0.234, 0.477));
  renderarea->setTitle(argv[0]);
  renderarea->setIconTitle(argv[0]);
  renderarea->viewAll();
  renderarea->show();

  printf("\nInstructions:\n");
  printf(" * [Q, W] Cycle colour schemes for fence.\n");
  printf(" * [E, R] Cycle colour schemes for walls.\n");
  printf(" * Use the mouse to manipulate the point-draggers on top of each fence-segment.\n");
  printf("\n\n");


  // Create an event callback which catches keypresses.
  SoEventCallback * event = new SoEventCallback;
  root->addChild(event);
  event->addEventCallback(SoKeyboardEvent::getClassTypeId(), keyboardCB, NULL);


  // Let the show begin!
  SoQt::show(window);
  SoQt::mainLoop();

  // Cleanup
  delete renderarea;
  root->unref();
  delete fieldsensor;
  delete voltexture;

  return 0;
}

// *************************************************************************

