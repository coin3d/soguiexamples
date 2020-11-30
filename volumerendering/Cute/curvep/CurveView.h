#ifndef CURVEVIEW_H
#define CURVEVIEW_H

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

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsItem>
#include <qimage.h>
#include <Inventor/SbBasic.h>
#include <Inventor/lists/SbList.h>

// FIXME: remove these dependencies. 20031020 mortene.
#include "SoQtColorTableEditor.h"
#include "ColorCurve.h"

class QMouseEvent;
class QGraphicsRectItem;

// *************************************************************************

class CurveView : public QGraphicsView 
{
  Q_OBJECT

public:
  CurveView(int numcolors,
            SoQtColorTableEditor::Mode mode, 
            QGraphicsScene * canvas, 
            QWidget * parent = 0, 
            const char * name = 0, 
            Qt::WindowFlags flags = 0);
  
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
  QGraphicsRectItem * newControlPoint(int x, int y);
  QList<QGraphicsItem*> newCanvasCtrlPtList(void);
  QGraphicsItem * smallestItem(QList<QGraphicsItem*> * list);
  SbBool mousepressed;
  QPoint movingstart;
  QPoint lastpos;

  QGraphicsScene * canvas;
  QGraphicsItem * movingitem;

  CurveType curvemode;
  SoQtColorTableEditor::Mode colormode;
  int colorindex;
  const int ptsize;
  int size;
  int maxval;
  
  SbList<QList<QGraphicsItem*>> canvasctrlpts;
  SbList<ColorCurve*> colorcurves;
    
  QList<QGraphicsItem*> curvesegments;
  QList<QGraphicsItem*> grid;
};

// *************************************************************************

#endif // CURVEVIEW_H
