#ifndef CVRTEST_VOLUMERENDERHANDLER_H
#define CVRTEST_VOLUMERENDERHANDLER_H

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

class SoVolumeRender;
class SoVolumeData;
class SoVolumeRender_ctrl;


class VolumeRenderHandler : QObject
{
  Q_OBJECT

public:
  VolumeRenderHandler(SoVolumeRender * node, const SoVolumeData * volumedatanode, QWidget * parent = NULL);
  ~VolumeRenderHandler();

private slots:
  void numSlicesSliderUpdate(int val);
  void numSlicesEditUpdate(void);
  void numSlicesControlUpdate(int idx);
  void interpolationUpdate(int idx);
  void compositionUpdate(int idx);
  void viewAlignedSlicesCheckBoxUpdate(int idx);

private:
  void initGUI(void);

  SoVolumeRender * node;
  const SoVolumeData * vdnode;
  SoVolumeRender_ctrl * ctrl;
};

#endif // !CVRTEST_VOLUMERENDERHANDLER_H
