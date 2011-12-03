#ifndef GRADIENT_VIEW_H
#define GRADIENT_VIEW_H

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

#include <qcanvas.h>
#include "Gradient.h"

class TickMark;
class QPainter;
class QMouseEvent;
class QResizeEvent;
class ImageItem;
class QPopupMenu;
class QStatusBar;

// *************************************************************************

class GradientView : public QCanvasView
{
  Q_OBJECT

public:
  GradientView(QCanvas * c = 0,
               const Gradient & g = Gradient(), 
               QWidget * parent = 0, 
               const char * name = 0, 
               WFlags f = 0);
  
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
  QCanvas * canvas;
  Gradient grad;
  ImageItem * graditem;
  ImageItem * selectionmarker;
  QPopupMenu * menu;
  QValueList<TickMark*> tickmarks;
  QStatusBar * statusbar;

  int currenttick;
  int segmentidx;
  float min, max;

  QPoint moving_start;
  SbBool mousepressed;
};

#endif // ! GRADIENT_VIEW_H
