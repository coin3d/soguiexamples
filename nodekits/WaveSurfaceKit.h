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

/**************************************************************************\
 * This class demonstrates how to extend Inventor by subclassing in order
 * to render a surface that represents water. We extend the SoShapeKit class
 * and define the appropriate material properties, texture coordinate generation
 * and so on. By extending SoShapeKit, much functionality is obtained for free
 * such as automatic generation of normals and picking. By defining a callback
 * function that accepts mouse clicks, the user can deploy drops in the water
 * by clicking the mouse when the cursor is over the surface. The class uses a
 * SoIdleSensor to animate the surface. The SoIdleSensor detects when the
 * processor is idle, and calls the idle function when this happens.
 *
 * To use this kit, simply insert it in the scene, as you would with any other
 * node or kit. Dont forget to call WaveSurfaceKit::initClass()!

\**************************************************************************/

#ifndef WAVESURFACEKIT_H
#define WAVESURFACEKIT_H

#include <Inventor/nodekits/SoShapeKit.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>

class SoIndexedTriangleStripSet;
class SoEventCallback;
class SoIdleSensor;
class SoFieldSensor;
class SoOneShotSensor;

class WaveSurfaceKit : public SoShapeKit
{
  SO_KIT_HEADER(WaveSurfaceKit);

public:
  WaveSurfaceKit(void);
  static void initClass(void);
  void startAnimation(void);
  void stopAnimation(void);
  void reset(void);
  
  SoSFInt32 width;
  SoSFInt32 height;
  SoSFBool pickOnBoundingBox;

private:
  virtual ~WaveSurfaceKit();
  void idle(void);
  void reshape(float x, float y, int dotsize);
  
  static void idleCallback(void * userData, SoSensor *);
  static void bboxfieldCallback(void * userData, SoSensor *);
  static void sizeChangedCallback(void * userData, SoSensor *);
  static void regenCallback(void * userData, SoSensor *);

  static void reshapeCallback(void * userData, SoEventCallback * eventCB);
  static void mouseDragCallback(void * userData, SoEventCallback * eventCB);
  
  void setDefaultValues();
  
  // Need to maintain 3 copies of vertex positions
  // due to the nature of the wave equation (3 time-steps)
  SbVec3f * vertexPositions0;
  SbVec3f * vertexPositions1;
  SbVec3f * vertexPositions2;

  SoOneShotSensor * oneshotsensor;
  SoIdleSensor * sensor;
  SoFieldSensor * bboxfieldsensor;
  SoFieldSensor * widthfieldsensor;
  SoFieldSensor * heightfieldsensor;
  
  // number of vertices in x and y direction
  SbBool leftbuttondown;
  
  // for speed
  int currentwidth;
  
  // Access functions for readability. Returns the height of the vertex position
  inline float & u2(int i,int j) { return vertexPositions2[i*this->currentwidth+j][2]; }
  inline float & u1(int i,int j) { return vertexPositions1[i*this->currentwidth+j][2]; }
  inline float & u0(int i,int j) { return vertexPositions0[i*this->currentwidth+j][2]; }
};

#endif // WAVESURFACEKIT_H

