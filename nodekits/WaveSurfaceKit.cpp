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

#include <Inventor/SbVec3f.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoIndexedTriangleStripSet.h>
#include <Inventor/nodes/SoTextureCoordinateEnvironment.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/sensors/SoIdleSensor.h>
#include <Inventor/sensors/SoOneShotSensor.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>

#include "WaveSurfaceKit.h"

SO_KIT_SOURCE(WaveSurfaceKit);

void WaveSurfaceKit::initClass()
{
  SO_KIT_INIT_CLASS(WaveSurfaceKit, SoShapeKit, "ShapeKit");
}

WaveSurfaceKit::WaveSurfaceKit(void)
{
  SO_KIT_CONSTRUCTOR(WaveSurfaceKit);
  SO_KIT_ADD_FIELD(pickOnBoundingBox, (TRUE));
  SO_KIT_ADD_FIELD(width, (70));
  SO_KIT_ADD_FIELD(height, (70));
  SO_KIT_INIT_INSTANCE();
  
  this->leftbuttondown = FALSE;
  this->bboxfieldsensor = new SoFieldSensor(bboxfieldCallback, this);
  this->bboxfieldsensor->attach(&this->pickOnBoundingBox);

  this->widthfieldsensor = new SoFieldSensor(sizeChangedCallback, this);
  this->widthfieldsensor->attach(&this->width);
  this->heightfieldsensor = new SoFieldSensor(sizeChangedCallback, this);
  this->heightfieldsensor->attach(&this->height);
  this->oneshotsensor = new SoOneShotSensor(regenCallback, this);

  // add an event callback function that responds to mouse clicks
  SoEventCallback* eventCB = new SoEventCallback;
  eventCB->addEventCallback(SoMouseButtonEvent::getClassTypeId(), WaveSurfaceKit::reshapeCallback, this);
  eventCB->addEventCallback(SoLocation2Event::getClassTypeId(), WaveSurfaceKit::mouseDragCallback, this);
  
  this->setPart("callbackList[0]", eventCB);
  
  // add a sensor that updates the surface whenever the processor is idle
  this->sensor = new SoIdleSensor(idleCallback,this);
  
  this->vertexPositions0 = NULL;
  this->vertexPositions1 = NULL;
  this->vertexPositions2 = NULL;

  // set up default geometry
  this->setDefaultValues();

  // set up default picking
  WaveSurfaceKit::bboxfieldCallback(this, this->bboxfieldsensor);
}

WaveSurfaceKit::~WaveSurfaceKit()
{
  delete this->widthfieldsensor;
  delete this->heightfieldsensor;
  delete this->oneshotsensor;
  delete this->sensor;
  
  delete[] this->vertexPositions0;
  delete[] this->vertexPositions1;
  delete[] this->vertexPositions2;
}

void WaveSurfaceKit::startAnimation()
{
  // start the sensor
  sensor->schedule();
}

void WaveSurfaceKit::stopAnimation()
{
  // stop the sensor
  sensor->unschedule();
}

void 
WaveSurfaceKit::bboxfieldCallback(void * userData, SoSensor *)
{
  WaveSurfaceKit * waveKit = (WaveSurfaceKit*) userData;
  SoPickStyle * ps = (SoPickStyle*) waveKit->getPart("pickStyle", TRUE);

  if (waveKit->pickOnBoundingBox.getValue()) {
    ps->style = SoPickStyle::BOUNDING_BOX;
  }
  else {
    ps->style = SoPickStyle::SHAPE;
  }  
}

void 
WaveSurfaceKit::sizeChangedCallback(void * userData, SoSensor *)
{
  WaveSurfaceKit * waveKit = (WaveSurfaceKit*) userData;
  waveKit->oneshotsensor->schedule();  
}

void 
WaveSurfaceKit::regenCallback(void * userData, SoSensor *)
{
  WaveSurfaceKit * waveKit = (WaveSurfaceKit*) userData;
  waveKit->setDefaultValues();
}

void WaveSurfaceKit::idleCallback(void* userData, SoSensor * s)
{
  WaveSurfaceKit * waveKit = (WaveSurfaceKit*) userData;
  waveKit->idle();
  
  // the sensor is rescheduled to call this method again
  // as soon as the processor is idle
  s->schedule();
}

// determine if the left mouse button is down or not
void WaveSurfaceKit::reshapeCallback(void* userData, SoEventCallback* eventCB)
{
  WaveSurfaceKit * waveKit = (WaveSurfaceKit*) userData;
  const SoMouseButtonEvent * mbe = (SoMouseButtonEvent *)eventCB->getEvent();
  
  if (mbe->getButton() == SoMouseButtonEvent::BUTTON1 &&
      mbe->getState() == SoButtonEvent::DOWN) {   
    waveKit->leftbuttondown = TRUE;
    // call this to update waves
    WaveSurfaceKit::mouseDragCallback(userData, eventCB);
  }
  else waveKit->leftbuttondown = FALSE;
}

void WaveSurfaceKit::mouseDragCallback(void* userData, SoEventCallback* eventCB)
{
  WaveSurfaceKit * waveKit = (WaveSurfaceKit*) userData;
  const SoEvent * mbe = (SoEvent *)eventCB->getEvent();
  
  if (waveKit->leftbuttondown) {
    // see if the surface was picked
    const SoPickedPoint* ppoint = eventCB->getPickedPoint();
    if(ppoint && ppoint->getPath() && ppoint->getPath()->containsNode(waveKit)) {
      SbVec3f v = ppoint->getPoint();
      
      // adjust the coordinates of the surface at the point picked
      waveKit->reshape(v[0],v[1],10);
    }
  }
}

// this function is called whenever the processor is idle. It updates
// the height of the surface according to the 2D Wave equation. On the
// boundaries, a neumann boundary condition is enforced (du/dn = 0)
void WaveSurfaceKit::idle(void)
{
  SoCoordinate3* coords = SO_GET_PART(this, "coordinate3", SoCoordinate3);

  int w = this->width.getValue();
  int h = this->height.getValue();
  
  // the step sizes must satisfy 0 < dt*dt/h*h <= 1 for the solution to be stable
  float dt = 0.3f;	// step size in time 
  float step = 1.0f;	// step size in space (same in x and y direction)
  float a = 0.1f;	// damping coefficient. (a = 0.0 -> no damping)
  
  // efficient to precalculate the coefficients
  float C = dt*dt/step*step;
  float B = 0.02f*a*dt;
  
  //update all inner points
  int i,j;
  for(i=1; i<w-1; i++) {
    for(j=1; j<h-1; j++) {
      u2(i,j) = (C*( u1(i-1,j) + u1(i+1,j) + u1(i,j-1) + u1(i,j+1) - 4*u1(i,j) ) + 2*u1(i,j) - u0(i,j) + B*u0(i,j))/(1+B);
    }
  }

  // update boundary points (homogenous neumann boundary condition)
  i=0;
  for(j=1; j<h-1; j++) {
    u2(i,j) = (C*( 2*u1(i+1,j) + u1(i,j-1) + u1(i,j+1) - 4*u1(i,j) ) + 2*u1(i,j) - u0(i,j) + B*u0(i,j))/(1+B);
  }
  i=w-1;
  for(j=1; j<h-1; j++) {
    u2(i,j) = (C*( 2*u1(i-1,j) + u1(i,j-1) + u1(i,j+1) - 4*u1(i,j) ) + 2*u1(i,j) - u0(i,j) + B*u0(i,j))/(1+B);
  }
  j=0;
  for(i=1; i<w-1; i++) {
    u2(i,j) = (C*( u1(i-1,j) + u1(i+1,j) + 2*u1(i,j+1) - 4*u1(i,j) ) + 2*u1(i,j) - u0(i,j) + B*u0(i,j))/(1+B);
  }
  j=h-1;
  for(i=1; i<w-1; i++) {
    u2(i,j) = (C*( u1(i-1,j) + u1(i+1,j) + 2*u1(i,j-1) - 4*u1(i,j) ) + 2*u1(i,j) - u0(i,j) + B*u0(i,j))/(1+B);			
  }
  
  // update corner points
  i=0; j=0;
  u2(i,j) = (C*( 2*u1(i+1,j) + 2*u1(i,j+1) - 4*u1(i,j) ) + 2*u1(i,j) - u0(i,j) + B*u0(i,j))/(1+B);
  i=w-1; j=0;
  u2(i,j) = (C*( 2*u1(i-1,j) + 2*u1(i,j+1) - 4*u1(i,j) ) + 2*u1(i,j) - u0(i,j) + B*u0(i,j))/(1+B);
  i=0; j=h-1;
  u2(i,j) = (C*( 2*u1(i+1,j) + 2*u1(i,j-1) - 4*u1(i,j) ) + 2*u1(i,j) - u0(i,j) + B*u0(i,j))/(1+B);
  i=w-1; j=h-1;
  u2(i,j) = (C*( 2*u1(i-1,j) + 2*u1(i,j-1) - 4*u1(i,j) ) + 2*u1(i,j) - u0(i,j) + B*u0(i,j))/(1+B);
  
  coords->point.setValues(0,w*h,this->vertexPositions2);
  
  // switch the arrays for the next time-step
  SbVec3f * temp = this->vertexPositions0;
  this->vertexPositions0 = this->vertexPositions1;
  this->vertexPositions1 = this->vertexPositions2;
  this->vertexPositions2 = temp;
}

// should be centered on (x,y). 
void WaveSurfaceKit::reshape(float xx, float yy, int dotsize)
{
  int w = this->width.getValue();
  int h = this->height.getValue();

  xx += 1.0f;
  xx *= (w-1)/2;
  yy += 1.0f;
  yy *= (h-1)/2;
  
  // get rounded coordinates for the hit point
  int x = int(xx+0.5f);
  int y = int(yy+0.5f);
  
  if((0 < x && x < w-dotsize-1) && (0 < y && y < h-dotsize-1)) {	
    float net_increment = 0.0;
    
    int i,j;
    // in order to make nice waves, it is best to move the vertices
    // in a smooth gaussian bell shaped top
    for(i=0; i<dotsize; i++)
      for(j=0; j<dotsize; j++) {
        float offset = 0.01f*sinf(float(i)*float(M_PI)/float(dotsize))*sinf(float(j)*float(M_PI)/float(dotsize));
        u1(i+x,j+y) += offset;
        u0(i+x,j+y) += offset;
        
        net_increment += offset;
      }
    
    // due to the neumann boundary condition we have to decrease all vertices
    // to make sure that the surface does not rise when waves are made
    float point_decrement = net_increment/((w-1)*(h-1));
    
    for(i=0; i<w; i++) { 
      for(j=0; j<h; j++) {
        u1(i,j) -= point_decrement;
        u0(i,j) -= point_decrement;
      }
    }
  }
}

// here we set up the ShapeKit with appropriate values
// in order to represent a transparent surface that looks
// like water
void WaveSurfaceKit::setDefaultValues(void)
{
  int w = this->width.getValue();
  int h = this->height.getValue();
  this->currentwidth = w; // update local cached value (using in inlined code)

  delete[] this->vertexPositions0;
  delete[] this->vertexPositions1;
  delete[] this->vertexPositions2;

  this->vertexPositions0 = new SbVec3f[w*h];
  this->vertexPositions1 = new SbVec3f[w*h];
  this->vertexPositions2 = new SbVec3f[w*h];

  int numIndices = (w-1)*(h*2+1);
  int numVertices = w*h;
  
  int * indices = new int[numIndices];
  
  int i,j;
  int k = 0;
  
  // generate vertex positions. The vertices are scaled and shifted
  // into the range -1 - 1 in x and y direction for convenience.
  for(i=0; i<w; i++) {
    for(j=0; j<h; j++) {
      this->vertexPositions0[k] = SbVec3f(float(2*i)/(w-1)-1.0f,float(2*j)/(h-1)-1.0f,0.0f);
      this->vertexPositions1[k] = SbVec3f(float(2*i)/(w-1)-1.0f,float(2*j)/(h-1)-1.0f,0.0f);
      this->vertexPositions2[k] = SbVec3f(float(2*i)/(w-1)-1.0f,float(2*j)/(h-1)-1.0f,0.0f);
      k++;
    }
  }
  
  k=0;
  // generate indices. -1 terminates each triangle strip
  for(i=0; i<w; i++) {
    for(j=0; j<h; j++) {
      indices[k] = i*h+j;
      indices[k+1] = (i+1)*h+j;
      
      // if we have reached the end of the surface, terminate the strip
      // and start a new one.
      if(j==h-1) {
        indices[k+2] = -1; k++;
      }
      k+=2;
    }
  }
   
  SoShapeHints* sHints = new SoShapeHints();
  // ensures double sided lighting
  sHints->vertexOrdering = SoShapeHints::COUNTERCLOCKWISE;
  // ensures smooth shading
  sHints->creaseAngle = 1.0f;
  
  // want normals to be calculated per vertex to get a smooth surface
  SoNormalBinding* normalBinding = new SoNormalBinding();
  normalBinding->value = SoNormalBinding::PER_VERTEX;
  
  // the surface should be transparent
  SoMaterial* material = new SoMaterial();
  material->transparency = 0.5f;
  
  // we want the surface to look shiny and reflective, use environment mapping
  SoTextureCoordinateEnvironment* texCoordEnv = new SoTextureCoordinateEnvironment();
  
  SoCoordinate3* vertexCoords = new SoCoordinate3();
  vertexCoords->point.setValues(0, numVertices, &this->vertexPositions1[0]);
  
  // use an indexed set of triangle strips for fast rendering
  SoIndexedTriangleStripSet* triangleStrips = new SoIndexedTriangleStripSet();
  triangleStrips->coordIndex.setValues(0, numIndices, indices);
  delete[] indices;

  // this sets the parts we've just made
  setPart("appearance.material", material);
  setPart("normalBinding", normalBinding);
  setPart("shapeHints", sHints);
  setPart("textureCoordinateFunction", texCoordEnv);
  setPart("coordinate3", vertexCoords);
  setPart("shape",triangleStrips);
}

// reset the height of the surface
void WaveSurfaceKit::reset(void)
{
  int w = this->width.getValue();
  int h = this->height.getValue();
  int k=0;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      this->vertexPositions0[k] = SbVec3f(float(2*i)/(w-1)-1.0f,float(2*j)/(h-1)-1.0f,0.0f);
      this->vertexPositions1[k] = SbVec3f(float(2*i)/(w-1)-1.0f,float(2*j)/(h-1)-1.0f,0.0f);
      this->vertexPositions2[k] = SbVec3f(float(2*i)/(w-1)-1.0f,float(2*j)/(h-1)-1.0f,0.0f);
      k++;
    }
  }
}
