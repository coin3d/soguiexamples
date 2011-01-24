#ifndef GRADIENT_VIEW_H
#define GRADIENT_VIEW_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <q3canvas.h>
#include "Gradient.h"

class TickMark;
class QPainter;
class QMouseEvent;
class QResizeEvent;
class ImageItem;
class Q3PopupMenu;
class QStatusBar;

// *************************************************************************

class GradientView : public Q3CanvasView
{
  Q_OBJECT

public:
  GradientView(Q3Canvas * c = 0,
               const Gradient & g = Gradient(), 
               QWidget * parent = 0, 
               const char * name = 0, 
               Qt::WFlags f = 0);
  
  ~GradientView();

  void setGradient(const Gradient & grad);
  const Gradient & getGradient(void) const;
  void insertTick(float t);
  void setChangeCallback(Gradient::ChangeCB * cb, void * userdata);
  void setDataLimits(float min, float max);
  QSize sizeHint(void) const;

public slots:
  void updateTicks(void);
  void updateView(void);
  
signals:
  void viewChanged(void);
  void tickSelected(void);
  void mouseMoved(int x);
  void ticksChanged(void);

protected:
  void contentsMousePressEvent(QMouseEvent *);
  void contentsMouseReleaseEvent(QMouseEvent *);
  void contentsMouseMoveEvent(QMouseEvent *);
  void viewportResizeEvent(QResizeEvent *);
  void buildMenu();
  void unselectAll(void);

private slots:
  void copySegmentColorRight(void);
  void copySegmentColorLeft(void);
  void chooseSegmentColorLeft(void);
  void chooseSegmentColorRight(void);
  void chooseTickColorLeft(void);
  void chooseTickColorRight(void);
  void copyTickColorLeft(void);
  void copyTickColorRight(void);
  void insertTick(void);
  void centerTick(void);
  void deleteTick(void);
  
private:
  void setGradientColor(unsigned int tickmarkidx, Gradient::TickSide side, QRgb col);
  void setGradientColor(unsigned int tickmarkidx, Gradient::TickSide side);


  TickMark * newTick(int x);
  Q3Canvas * canvas;
  Gradient grad;
  ImageItem * graditem;
  ImageItem * selectionmarker;
  Q3PopupMenu * menu;
  Q3ValueList<TickMark*> tickmarks;
  QStatusBar * statusbar;

  int currenttick;
  int segmentidx;
  float min, max;

  QPoint moving_start;
  SbBool mousepressed;
};

#endif // ! GRADIENT_VIEW_H
