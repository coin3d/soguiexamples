#ifndef CURVEVIEW_H
#define CURVEVIEW_H

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
#include <qimage.h>
#include <Inventor/SbBasic.h>
#include <Inventor/lists/SbList.h>
#include <QtCore/qnamespace.h>
#include <QResizeEvent>
#include <QMouseEvent>

// FIXME: remove these dependencies. 20031020 mortene.
#include "SoQtColorTableEditor.h"
#include "ColorCurve.h"

class Q3CanvasItemList;
class QMouseEvent;
class Q3CanvasItem;

// *************************************************************************
class CurveView : public Q3CanvasView 
{
  Q_OBJECT

public:
  CurveView(int numcolors,
            SoQtColorTableEditor::Mode mode, 
            Q3Canvas * canvas, 
            QWidget * parent = 0, 
            const char * name = 0, 
            Qt::WFlags flags = 0);
  
  ~CurveView();

  enum CurveType { SMOOTH, FREE };
  
  void setMode(SoQtColorTableEditor::Mode mode);
  void setColors(uint8_t * colors, int num);
  void getColors(uint8_t * colors, int num) const;
  void setCallBack(ColorCurve::ChangeCB * cb, void * userData);
  QPixmap getPixmap(int width, int height) const;
  QPixmap getGradient(int width, int height) const;

public slots:
  void changeColorMode(int mode);
  void changeCurveMode(int mode);
  void setConstantValue(int value);
  void resetActive(void);
signals:
  void curveChanged(void);
  
protected:
  virtual void contentsMousePressEvent(QMouseEvent * e);
  virtual void contentsMouseReleaseEvent(QMouseEvent * e);
  virtual void contentsMouseMoveEvent(QMouseEvent * e);
  virtual void drawContents(QPainter * p, int cx, int cy, int cw, int ch);

private:
  virtual void drawContents(QPainter * p);
  void interpolateFromColors();
  void initColorCurves(void);
  void initCanvasCurve(void);
  void hideUnselected(void);
  void updateCurve(void);
  void initGrid(void);
  
  QPixmap makePixmap(int w, int h, const uint8_t * r, const uint8_t * g, const uint8_t * b) const;
  Q3CanvasRectangle * newControlPoint(int x, int y);
  Q3CanvasItemList newCanvasCtrlPtList(void);
  Q3CanvasItem * smallestItem(Q3CanvasItemList * list);

  SbBool mousepressed;
  QPoint movingstart;
  QPoint lastpos;
  Q3Canvas * canvas;
  Q3CanvasItem * movingitem;

  CurveType curvemode;
  SoQtColorTableEditor::Mode colormode;
  int colorindex;
  const int ptsize;
  int size;
  int maxval;
  
  SbList<Q3CanvasItemList> canvasctrlpts;
  SbList<ColorCurve*> colorcurves;
    
  Q3CanvasItemList curvesegments;
  Q3CanvasItemList grid;
};

// *************************************************************************
#endif // CURVEVIEW_H
