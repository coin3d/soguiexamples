#ifndef SOGUIEXAMPLES_OPAQUECHAIR_H
#define SOGUIEXAMPLES_OPAQUECHAIR_H

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

class SoSeparator;
class SoFieldSensor;
class SoText2;
class SmAxisKit;
class SoOrthoSlice;

// *************************************************************************

class OpaqueChair {
public:
  OpaqueChair(const char * filename);
  ~OpaqueChair();
  
  SbBool loadVolumeData(const char * filename);
  SoSeparator * getSceneGraph();
  void setAxisRange(unsigned int axis, float start, float stop, float interval);

private:
  SoSeparator * opaquechairroot;
  SoOrthoSlice * orthoslice[3];
  SoTranslation * clipplanetrans[3];
  SoTranslation * axislabeltrans[3];
  SoText2 * axislabel[3];
  SoFieldSensor * draggersensor[3];

  float draggerrange[3];

  SbVec3f volumedims;
  SbVec3s volumeslices;

  void loadInventorFile();
  void setupDraggers();
  void setupGeometry();
  void setupAxisMarkers(SmAxisKit * kit, float start, float stop, float interval);

  void draggerCBCommon(SoSensor * sensor, unsigned int axis);
  static void draggerXCB(void * data, SoSensor * sensor);
  static void draggerYCB(void * data, SoSensor * sensor);
  static void draggerZCB(void * data, SoSensor * sensor);
};

#endif // ! SOGUIEXAMPLES_OPAQUECHAIR_H
