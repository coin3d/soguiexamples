
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

OpaqueChair::OpaqueChair(const char * filename)
{ 
  
  this->opaquechairroot = NULL;

  this->bottominsideorthoslice = NULL;
  this->leftinsideorthoslice = NULL;
  this->backinsideorthoslice = NULL;

  this->draggerXSensor = NULL;
  this->draggerYSensor = NULL;
  this->draggerZSensor = NULL;

  this->leftclipplanetrans = NULL;
  this->bottomclipplanetrans = NULL;
  this->backclipplanetrans = NULL;

  this->axisxlabeltrans = NULL;
  this->axisylabeltrans = NULL;
  this->axiszlabeltrans = NULL;

  this->axisxlabel = NULL;
  this->axisylabel = NULL;
  this->axiszlabel = NULL;

  loadInventorFile();
  loadVolumeData(filename);

}

OpaqueChair::~OpaqueChair()
{

  delete this->draggerXSensor;
  delete this->draggerYSensor;
  delete this->draggerZSensor;

}

/*************************************************************************************/

void
OpaqueChair::draggerXCB(void * data, SoSensor * sensor)
{
  OpaqueChair * oc = (OpaqueChair *) data;
  SoFieldSensor * fs = (SoFieldSensor *) sensor;
  SoSFVec3f * trans = (SoSFVec3f *) fs->getAttachedField();

  const int slice = SbMax(0, (int) (oc->volumeslices[0] * (trans->getValue()[0]/oc->draggerXRange) - 1));
  oc->leftinsideorthoslice->sliceNumber.setValue(slice);

  const float ctrans = (trans->getValue()[0]/oc->draggerXRange) * oc->volumedims[0] - oc->volumedims[0]/2.0f;
  oc->leftclipplanetrans->translation.setValue(ctrans, 0.0f, 0.0f);

  SbString str;
  oc->axisxlabeltrans->translation.setValue(ctrans + oc->volumedims[0]/2.0f, 0.0f, 0.0f);
  oc->axisxlabel->string.setValue(str.sprintf("  [%d]", slice));
  
}

void
OpaqueChair::draggerYCB(void * data, SoSensor * sensor)
{
  OpaqueChair * oc = (OpaqueChair *) data;
  SoFieldSensor * fs = (SoFieldSensor *) sensor;
  SoSFVec3f * trans = (SoSFVec3f *) fs->getAttachedField();

  const int slice = SbMax(0, (int) (oc->volumeslices[1] * (trans->getValue()[0]/oc->draggerYRange) - 1));
  oc->bottominsideorthoslice->sliceNumber.setValue(slice);

  const float ctrans = (trans->getValue()[0]/oc->draggerYRange) * oc->volumedims[1] - oc->volumedims[1]/2.0f;
  oc->bottomclipplanetrans->translation.setValue(0.0f, ctrans, 0.0f);

  SbString str;
  oc->axisylabeltrans->translation.setValue(0.0f, ctrans + oc->volumedims[1]/2.0f, 0.0f);
  oc->axisylabel->string.setValue(str.sprintf("  [%d]", slice));

}

void
OpaqueChair::draggerZCB(void * data, SoSensor * sensor)
{
  OpaqueChair * oc = (OpaqueChair *) data;
  SoFieldSensor * fs = (SoFieldSensor *) sensor;
  SoSFVec3f * trans = (SoSFVec3f *) fs->getAttachedField();

  const int slice = SbMax(0, (int) (oc->volumeslices[2] * (trans->getValue()[0]/oc->draggerZRange) - 1));
  oc->backinsideorthoslice->sliceNumber.setValue(slice);

  const float ctrans = (trans->getValue()[0]/oc->draggerZRange) * oc->volumedims[2] - oc->volumedims[2]/2.0f;
  oc->backclipplanetrans->translation.setValue(0.0f, 0.0f, ctrans);
 
  SbString str;
  oc->axiszlabeltrans->translation.setValue(0.0f, 0.0f, ctrans + oc->volumedims[2]/2.0f);
  oc->axiszlabel->string.setValue(str.sprintf("  [%d]", slice));

}


/*************************************************************************************/


void
OpaqueChair::loadInventorFile()
{

  SoInput in;
  if (in.openFile("OpaqueChair.iv")) {
    this->opaquechairroot = SoDB::readAll(&in);
    if (!opaquechairroot) {
      SoDebugError::postInfo("loadInventorFile", "Error parsing 'OpaqueChair.iv'! Aborting.");
      assert(FALSE);
    }
  } else {
    SoDebugError::postInfo("loadInventorFile", "Could find 'OpaqueChair.iv'! Aborting.");
    assert(FALSE);
  }
    
}

void
OpaqueChair::setupDraggers()
{

  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");
  SoVolumeData * voldat = (SoVolumeData *) this->opaquechairroot->getByName(SbName("Volumedata"));
   
  const SbBox3f dims = voldat->getVolumeSize();
  this->volumedims[0] = SbAbs(dims.getMax()[0]) + SbAbs(dims.getMin()[0]);
  this->volumedims[1] = SbAbs(dims.getMax()[1]) + SbAbs(dims.getMin()[1]);
  this->volumedims[2] = SbAbs(dims.getMax()[2]) + SbAbs(dims.getMin()[2]);

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
  if (!this->draggerXSensor) this->draggerXSensor = new SoFieldSensor(draggerXCB, this);
  if (!this->draggerYSensor) this->draggerYSensor = new SoFieldSensor(draggerYCB, this);
  if (!this->draggerZSensor) this->draggerZSensor = new SoFieldSensor(draggerZCB, this);

  // Fetch ortho slice nodes
  this->bottominsideorthoslice = 
    (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("BottomInsideSlice"));
  this->leftinsideorthoslice = 
    (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("LeftInsideSlice"));
  this->backinsideorthoslice = 
    (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("BackInsideSlice"));

  // Fetch clip plane translation nodes
  this->leftclipplanetrans = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("LeftClipPlaneTrans"));
  this->backclipplanetrans = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("BackClipPlaneTrans"));
  this->bottomclipplanetrans = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("BottomClipPlaneTrans"));

  // Fetch dragger label translation nodes
  this->axisxlabeltrans = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("AxisXLabelTrans"));
  this->axisylabeltrans = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("AxisYLabelTrans"));
  this->axiszlabeltrans = 
    (SoTranslation *) this->opaquechairroot->getByName(SbName("AxisZLabelTrans"));

  // Fetch dragger text label nodes
  this->axisxlabel = 
    (SoText2 *) this->opaquechairroot->getByName(SbName("AxisXLabel"));
  this->axisylabel = 
    (SoText2 *) this->opaquechairroot->getByName(SbName("AxisYLabel"));
  this->axiszlabel = 
    (SoText2 *) this->opaquechairroot->getByName(SbName("AxisZLabel"));


  // Setup dragger range and attach field sensors
  SmRangeTranslate1Dragger * dragger;
  dragger = 
    (SmRangeTranslate1Dragger *) this->opaquechairroot->getByName(SbName("AxisXDragger"));
  this->draggerXRange = (this->volumedims[0]) / (width * draggerlen);
  dragger->range.setValue(0.0f, this->draggerXRange);
  this->draggerXSensor->attach(&dragger->translation);
  dragger->translation.setValue((this->volumedims[0]/2.0f) / (width * draggerlen), 0.0f, 0.0f);

  dragger = 
    (SmRangeTranslate1Dragger *) this->opaquechairroot->getByName(SbName("AxisYDragger"));
  this->draggerYRange = (this->volumedims[1])  / (width * draggerlen);
  dragger->range.setValue(0.0f, this->draggerYRange);
  this->draggerYSensor->attach(&dragger->translation);
  dragger->translation.setValue((this->volumedims[1]/2.0f) / (width * draggerlen), 0.0f, 0.0f);

  dragger = 
    (SmRangeTranslate1Dragger *) this->opaquechairroot->getByName(SbName("AxisZDragger"));
  this->draggerZRange = (this->volumedims[2]) / (width * draggerlen);
  dragger->range.setValue(0.0f, this->draggerZRange);
  this->draggerZSensor->attach(&dragger->translation);
  dragger->translation.setValue((this->volumedims[2]/2.0f) / (width * draggerlen), 0.0f, 0.0f);


}


void
OpaqueChair::setupGeometry()
{
  
  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");
  SoVolumeData * voldat = (SoVolumeData *) this->opaquechairroot->getByName(SbName("Volumedata"));
   
  SoOrthoSlice * slice;
  slice = (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("TopLSlice"));
  slice->sliceNumber.setValue((int) this->volumeslices[1] - 1);

  slice = (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("RightLSlice"));
  slice->sliceNumber.setValue((int) this->volumeslices[0] - 1);
  
  slice = (SoOrthoSlice *) this->opaquechairroot->getByName(SbName("FrontLSlice"));
  slice->sliceNumber.setValue((int) this->volumeslices[2] - 1);

  setXAxisRange(0.0f, 50.0f, 5.0f); // Default values
  setYAxisRange(0.0f, 50.0f, 5.0f);
  setZAxisRange(0.0f, 50.0f, 5.0f);

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
  assert(voldat->getVolumeData(this->volumeslices, discardptr, type));
   
  setupDraggers(); // Make the draggers fit the new data set
  setupGeometry();

}

SoSeparator *
OpaqueChair::getSceneGraph()
{
  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");
  return this->opaquechairroot;
}


void 
OpaqueChair::setXAxisRange(float start, float stop, float interval)
{
  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");

  SmAxisKit * kit = (SmAxisKit *) this->opaquechairroot->getByName(SbName("AxisX"));
  setupAxisMarkers(kit, start, stop, interval);

  const float length = SbAbs(stop) - SbAbs(start);
  SoScale * scale;
  scale = (SoScale *) this->opaquechairroot->getByName(SbName("AxisXScale"));
  scale->scaleFactor.setValue(this->volumedims[0]/length, 1.0f, 1.0f);

  SoTranslation * trans;
  trans = (SoTranslation *) this->opaquechairroot->getByName(SbName("AxisXTrans"));
  trans->translation.setValue(this->volumedims[0]/2.0f, this->volumedims[1], 0.0f);

}
 

void 
OpaqueChair::setYAxisRange(float start, float stop, float interval)
{
  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");

  SmAxisKit * kit = (SmAxisKit *) this->opaquechairroot->getByName(SbName("AxisY"));
  setupAxisMarkers(kit, start, stop, interval);

  const float length = SbAbs(stop) - SbAbs(start);
  SoScale * scale;
  scale = (SoScale *) this->opaquechairroot->getByName(SbName("AxisYScale"));
  scale->scaleFactor.setValue(this->volumedims[1]/length, 1.0f, 1.0f);

  SoTranslation * trans;
  trans = (SoTranslation *) this->opaquechairroot->getByName(SbName("AxisYTrans"));
  trans->translation.setValue(0.0f, this->volumedims[1]/2.0f, this->volumedims[2]);

}
 

void 
OpaqueChair::setZAxisRange(float start, float stop, float interval)
{
  assert(this->opaquechairroot && "Scene graph not loaded yet! Fatal error.");

  SmAxisKit * kit = (SmAxisKit *) this->opaquechairroot->getByName(SbName("AxisZ"));
  setupAxisMarkers(kit, start, stop, interval);
 
  const float length = SbAbs(stop) - SbAbs(start);
  SoScale * scale;
  scale = (SoScale *) this->opaquechairroot->getByName(SbName("AxisZScale"));
  scale->scaleFactor.setValue(this->volumedims[2]/length, 1.0f, 1.0f);

  SoTranslation * trans;
  trans = (SoTranslation *) this->opaquechairroot->getByName(SbName("AxisZTrans"));
  trans->translation.setValue(0.0f, this->volumedims[1], this->volumedims[2]/2.0f);

}

