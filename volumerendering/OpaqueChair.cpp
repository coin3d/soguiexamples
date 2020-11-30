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

#include <Inventor/SbName.h>
#include <Inventor/SoInput.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/nodes/SoClipPlane.h>
#include <Inventor/nodes/SoText2.h>

#include <VolumeViz/nodes/SoVolumeData.h>
#include <VolumeViz/nodes/SoOrthoSlice.h>
#include <SmallChange/draggers/SmRangeTranslate1Dragger.h>
#include <SmallChange/nodekits/SmAxisKit.h>

#include "OpaqueChair.h"
#include "OpaqueChair-iv.h"

OpaqueChair::OpaqueChair(const char * filename)
{ 
  
  this->opaquechairroot = NULL;

  for (unsigned int i=0; i < 3; i++) {
    this->orthoslice[i] = NULL;
    this->draggersensor[i] = NULL;
    this->clipplanetrans[i] = NULL;
    this->axislabeltrans[i] = NULL;
    this->axislabel[i] = NULL;
  }

  this->loadInventorFile();
  this->loadVolumeData(filename);
}

OpaqueChair::~OpaqueChair()
{
  for (unsigned int i=0; i < 3; i++) {
    delete this->draggersensor[i];
  }
}

/*************************************************************************************/

void
OpaqueChair::draggerCBCommon(SoSensor * sensor, unsigned int axis)
{
  SoFieldSensor * fs = (SoFieldSensor *) sensor;
  SoSFVec3f * trans = (SoSFVec3f *) fs->getAttachedField();

  const float normalizedpos = trans->getValue()[0] / this->draggerrange[axis];

  unsigned int slice = (unsigned int)
    ((this->volumeslices[axis] - 1) * normalizedpos);

  this->orthoslice[axis]->sliceNumber.setValue(slice);

  const float ctrans = normalizedpos * this->volumedims[axis] - this->volumedims[axis]/2.0f;
  SbVec3f v(0, 0, 0);
  v[axis] = ctrans;
  this->clipplanetrans[axis]->translation = v;

  if (this->axislabel[axis]) {
    v[axis] += this->volumedims[axis]/2.0f;
    this->axislabeltrans[axis]->translation = v;
    SbString str;
    this->axislabel[axis]->string.setValue(str.sprintf("  [%d]", slice));
  }
}

void
OpaqueChair::draggerXCB(void * data, SoSensor * sensor)
{
  OpaqueChair * oc = (OpaqueChair *) data;
  oc->draggerCBCommon(sensor, 0);
}

void
OpaqueChair::draggerYCB(void * data, SoSensor * sensor)
{
  OpaqueChair * oc = (OpaqueChair *) data;
  oc->draggerCBCommon(sensor, 1);
}

void
OpaqueChair::draggerZCB(void * data, SoSensor * sensor)
{
  OpaqueChair * oc = (OpaqueChair *) data;
  oc->draggerCBCommon(sensor, 2);
}


/*************************************************************************************/


void
OpaqueChair::loadInventorFile()
{
  SoInput in;
  in.setBuffer((void *)opaquechair_scene, strlen(opaquechair_scene));
  this->opaquechairroot = SoDB::readAll(&in);
  assert(opaquechairroot);
}

void
OpaqueChair::setupDraggers()
{
  unsigned int i;

  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");
  SoVolumeData * voldat = (SoVolumeData *) this->opaquechairroot->getByName(SbName("Volumedata"));
   
  const SbBox3f dims = voldat->getVolumeSize();
  for (i=0; i < 3; i++) {
    this->volumedims[i] = SbAbs(dims.getMax()[i]) + SbAbs(dims.getMin()[i]);
  }

  SoTranslation * origotrans = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("OrigoTranslation"));
  origotrans->translation.setValue(dims.getMax());

  const float draggerlen = 3.0f;
  // Dragger width is 1/20 of max volume dimension
  float width = SbMax(dims.getMax()[0], dims.getMax()[1]);
  width = (SbMax(width, dims.getMax()[2])) / 20.0f;   
  const float draggerspacing = width * 4.0f;

  SoTranslation * trans;
  trans = (SoTranslation *) this->opaquechairroot->getByName(SbName("AxisXDraggerTrans"));
  trans->translation.setValue(0.0f, 0.0f, this->volumedims[2] + draggerspacing);

  trans = (SoTranslation *) this->opaquechairroot->getByName(SbName("AxisYDraggerTrans"));
  trans->translation.setValue(this->volumedims[0] + draggerspacing, 0.0f, 0.0f);

  trans = (SoTranslation *) this->opaquechairroot->getByName(SbName("AxisZDraggerTrans"));
  trans->translation.setValue(this->volumedims[0] + draggerspacing, 0.0f, 0.0f);

  // Setup dragger scale
  SoScale * scale;
  scale = (SoScale *) this->opaquechairroot->getByName(SbName("AxisXDraggerScale"));
  scale->scaleFactor.setValue(width * draggerlen, width, 1.0f);
  
  scale = (SoScale *) this->opaquechairroot->getByName(SbName("AxisYDraggerScale"));
  scale->scaleFactor.setValue(width * draggerlen, width, 1.0f);
  
  scale = (SoScale *) this->opaquechairroot->getByName(SbName("AxisZDraggerScale"));
  scale->scaleFactor.setValue(width * draggerlen, width, 1.0f);
    
  // Setup dragger field sensors
  if (!this->draggersensor[0]) this->draggersensor[0] = new SoFieldSensor(draggerXCB, this);
  if (!this->draggersensor[1]) this->draggersensor[1] = new SoFieldSensor(draggerYCB, this);
  if (!this->draggersensor[2]) this->draggersensor[2] = new SoFieldSensor(draggerZCB, this);

  // Fetch ortho slice nodes
  this->orthoslice[1] = 
    (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("BottomInsideSlice"));
  this->orthoslice[0] = 
    (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("LeftInsideSlice"));
  this->orthoslice[2] = 
    (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("BackInsideSlice"));

  // Fetch clip plane translation nodes
  this->clipplanetrans[0] = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("LeftClipPlaneTrans"));
  this->clipplanetrans[2] = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("BackClipPlaneTrans"));
  this->clipplanetrans[1] = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("BottomClipPlaneTrans"));

  // Fetch dragger text labels, with translation nodes
  SbString str;
  static const char * axis[] = { "X", "Y", "Z" };
  for (i=0; i < 3; i++) {
    this->axislabeltrans[i] = (SoTranslation *)
      this->opaquechairroot->getByName(str.sprintf("Axis%sLabelTrans", axis[i]).getString());
    this->axislabel[i] = (SoText2 *)
      this->opaquechairroot->getByName(str.sprintf("Axis%sLabel", axis[i]).getString());
  }

  // Setup dragger range and attach field sensors
  SmRangeTranslate1Dragger * dragger;
  dragger = 
    (SmRangeTranslate1Dragger *) this->opaquechairroot->getByName(SbName("AxisXDragger"));
  this->draggerrange[0] = (this->volumedims[0]) / (width * draggerlen);
  dragger->range.setValue(0.0f, this->draggerrange[0]);
  this->draggersensor[0]->attach(&dragger->translation);
  dragger->translation.setValue((this->volumedims[0]/2.0f) / (width * draggerlen), 0.0f, 0.0f);

  dragger = 
    (SmRangeTranslate1Dragger *) this->opaquechairroot->getByName(SbName("AxisYDragger"));
  this->draggerrange[1] = (this->volumedims[1])  / (width * draggerlen);
  dragger->range.setValue(0.0f, this->draggerrange[1]);
  this->draggersensor[1]->attach(&dragger->translation);
  dragger->translation.setValue((this->volumedims[1]/2.0f) / (width * draggerlen), 0.0f, 0.0f);

  dragger = 
    (SmRangeTranslate1Dragger *) this->opaquechairroot->getByName(SbName("AxisZDragger"));
  this->draggerrange[2] = (this->volumedims[2]) / (width * draggerlen);
  dragger->range.setValue(0.0f, this->draggerrange[2]);
  this->draggersensor[2]->attach(&dragger->translation);
  dragger->translation.setValue((this->volumedims[2]/2.0f) / (width * draggerlen), 0.0f, 0.0f);
}


void
OpaqueChair::setupGeometry()
{
  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");
   
  SoOrthoSlice * slice;
  slice = (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("TopLSlice"));
  slice->sliceNumber.setValue((int) this->volumeslices[1] - 1);

  slice = (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("RightLSlice"));
  slice->sliceNumber.setValue((int) this->volumeslices[0] - 1);
  
  slice = (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("FrontLSlice"));
  slice->sliceNumber.setValue((int) this->volumeslices[2] - 1);

  for (unsigned int i=0; i < 3; i++) {
    this->setAxisRange(i, 0.0f, 50.0f, 5.0f); // Default values
  }
}


void
OpaqueChair::setupAxisMarkers(SmAxisKit * kit, float start, float stop, float interval)
{

  float markerheight = SbMax(this->volumedims[0], this->volumedims[1]);
  markerheight = SbMax(markerheight, this->volumedims[2]);

  kit->axisRange.setValue(SbVec2f(start, stop));
  kit->markerInterval.setValue(interval);
  kit->textInterval.setValue(interval * 2.0f); // Text label every 2nd marker
  kit->markerHeight.setValue(markerheight / 40.0f); // marker height is 1/40 of volume size
}


/*************************************************************************************/


SbBool
OpaqueChair::loadVolumeData(const char * filename)
{

  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");
  SoVolumeData * voldat = (SoVolumeData *) this->opaquechairroot->getByName(SbName("Volumedata"));
  voldat->fileName.setValue(filename);
  
  void * discardptr;
  SoVolumeData::DataType type;
  SbBool success = voldat->getVolumeData(this->volumeslices, discardptr, type);
  assert(success);
   
  this->setupDraggers(); // Make the draggers fit the new data set
  this->setupGeometry();

  return TRUE;
}

SoSeparator *
OpaqueChair::getSceneGraph()
{
  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");
  return this->opaquechairroot;
}


void 
OpaqueChair::setAxisRange(unsigned int axis, float start, float stop, float interval)
{
  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");

  SbString str;
  static const char * axisstr[] = { "X", "Y", "Z" };
  SmAxisKit * kit = (SmAxisKit *)
    this->opaquechairroot->getByName(str.sprintf("Axis%s", axisstr[axis]).getString());
  if (!kit) { return; }
  this->setupAxisMarkers(kit, start, stop, interval);

  const float length = SbAbs(stop) - SbAbs(start);

  SoScale * scale = (SoScale *)
    this->opaquechairroot->getByName(str.sprintf("Axis%sScale", axisstr[axis]).getString());
  SoTranslation * trans = (SoTranslation *)
    this->opaquechairroot->getByName(str.sprintf("Axis%sTrans", axisstr[axis]).getString());

  if (axis == 0) {
    scale->scaleFactor.setValue(this->volumedims[0]/length, 1.0f, 1.0f);
    trans->translation.setValue(this->volumedims[0]/2.0f, this->volumedims[1], 0.0f);
  }
  else if (axis == 1) {
    scale->scaleFactor.setValue(this->volumedims[1]/length, 1.0f, 1.0f);
    trans->translation.setValue(0.0f, this->volumedims[1]/2.0f, this->volumedims[2]);
  }
  else {
    scale->scaleFactor.setValue(this->volumedims[2]/length, 1.0f, 1.0f);
    trans->translation.setValue(0.0f, this->volumedims[1], this->volumedims[2]/2.0f);
  }
}
