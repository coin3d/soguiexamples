#ifndef CVRTEST_ORTHOSLICEHANDLER_H
#define CVRTEST_ORTHOSLICEHANDLER_H

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

#include <qwidget.h>

class SoOrthoSlice;
class SoVolumeData;
class SoOrthoSlice_ctrl;


class OrthoSliceHandler : QObject
{
  Q_OBJECT

public:
  OrthoSliceHandler(SoOrthoSlice * node, const SoVolumeData * volumedatanode, QWidget * parent = NULL);
  ~OrthoSliceHandler();

private slots:
  void sliceNumberSliderUpdate(int val);
  void sliceNumberEditUpdate(void);
  void axisUpdate(int idx);
  void interpolationUpdate(int idx);
  void alphaUseUpdate(int idx);
  void clippingCheckBoxUpdate(int idx);
  void clippingSideUpdate(int idx);

private:
  void initGUI(void);

  SoOrthoSlice * node;
  const SoVolumeData * vdnode;
  SoOrthoSlice_ctrl * ctrl;
};

#endif // !CVRTEST_ORTHOSLICEHANDLER_H
