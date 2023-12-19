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

#include <cassert>
#include <qpoint.h>
#include <qpainter.h>
#include <qcursor.h>
#include <qevent.h>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <Inventor/SbLinear.h>
#include "ColorCurve.h"
#include "CurveView.h"
//#include "moc_CurveView.icc"


CurveView::CurveView(int numcolors,
                     SoQtColorTableEditor::Mode mode,
                     QGraphicsScene * canvas,
                     QWidget * parent,
                     const char * name,
                     Qt::WindowFlags flags)

 : QGraphicsView(canvas, parent), ptsize(3)
{
  this->setObjectName(name);
  this->setWindowFlags(flags);
  this->colormode = mode;
  this->canvas = canvas;
  this->canvas->setSceneRect(QRect(QPoint(0, 0), QSize(numcolors, numcolors)));
  this->setFixedSize(numcolors+2, numcolors+2);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  this->curvemode = CurveView::SMOOTH;
  this->mousepressed = FALSE;
  this->movingitem = NULL;

  this->size = numcolors;
  this->initColorCurves();
  this->hideUnselected();

  this->initGrid();
  this->initCanvasCurve();
  this->viewport()->setMouseTracking(TRUE);
}

CurveView::~CurveView()
{
  for (int i = 0; i < this->colormode; i++) {
    delete this->colorcurves[i];
  }
}

void
CurveView::initColorCurves()
{
  for (int i = 0; i < this->colormode; i++) {
    this->colorindex = i;
    ColorCurve::CurveType type = ColorCurve::LINEAR;
    if (((this->colormode == SoQtColorTableEditor::LUMINANCE_ALPHA) && (i == 1)) ||
        ((this->colormode == SoQtColorTableEditor::RGBA) && (i == 3))){
      type = ColorCurve::CONSTANT;
    }

    this->colorcurves.append(new ColorCurve(type, this->size));
    this->canvasctrlpts.append(this->newCanvasCtrlPtList());
  }
  this->colorindex = 0;
}

void
CurveView::initCanvasCurve()
{
  const uint8_t * curvepts = this->colorcurves[this->colorindex]->getColorMap();
  for (int i = 2; i < this->colorcurves[this->colorindex]->getNumColors(); i+=2) {
    QGraphicsLineItem * line = new QGraphicsLineItem;
    line->setLine(i-2, int(this->size - 1) - curvepts[i-2], i, int(this->size - 1) - curvepts[i]);
    line->setZValue(1); // to make the curve be drawn on top of the grid
    line->show();
    this->canvas->addItem(line);
    this->curvesegments.append(line);
  }
}

void CurveView::initGrid()
{
  int step = this->size/4;
  QPen pen(Qt::gray);

  for (int i = step; i < this->size; i+=step) {
    QGraphicsLineItem * line = new QGraphicsLineItem;
    line->setLine(i, 0, i, (this->size - 1));
    line->setPen(pen);
    line->show();
    this->canvas->addItem(line);
    this->grid.append(line);
  }

  for (int j = step; j < this->size; j+=step) {
    QGraphicsLineItem * line = new QGraphicsLineItem;
    line->setLine(0, j, this->size, j);
    line->setPen(pen);
    line->show();
    this->canvas->addItem(line);
    this->grid.append(line);
  }
}

void CurveView::contentsMousePressEvent(QMouseEvent* e)
{
  if (e->button() == Qt::LeftButton) {
    this->mousepressed = TRUE;
  }
#if QT_VERSION >= 0x050D00
  QPoint p = transform().inverted().map(e->pos());
#else
  QPoint p = matrix().inverted().map(e->pos());
#endif
  this->movingstart = p;
  this->lastpos = p;
  QList<QGraphicsItem*> list = this->canvas->items(p);

  if (this->curvemode == CurveView::SMOOTH) {

    QList<QGraphicsItem*>::Iterator it = list.begin();

    if ((it != list.end()) && ((*it)->type() == QGraphicsRectItem::Type)) {
      if (e->button() == Qt::LeftButton) {
        this->movingitem = (*it);
      } else {
        if (this->canvasctrlpts[this->colorindex].size() > 2) {
          delete (*it);
          this->canvasctrlpts[this->colorindex].removeAll(*it);
        }
      }
    } else {
      if (e->button() == Qt::LeftButton) {
        QGraphicsRectItem * ctrlpt = this->newControlPoint(p.x(), p.y());
        this->movingitem = ctrlpt;
        this->canvasctrlpts[this->colorindex].append(ctrlpt);
      }
    }
    this->updateCurve();
  }

  this->canvas->update();
}

void
CurveView::contentsMouseReleaseEvent(QMouseEvent * e)
{
  this->mousepressed = FALSE;
  this->colorcurves[this->colorindex]->notify();
}

void
CurveView::contentsMouseMoveEvent(QMouseEvent* e)
{
  QPoint p = matrix().inverted().map(e->pos());

  if (this->curvemode == CurveView::SMOOTH) {
    // change the cursor if it is over a control point
    QList<QGraphicsItem*> list = this->canvas->items(p);
    QList<QGraphicsItem*>::Iterator it = list.begin();

    if ((it != list.end()) && ((*it)->type() == QGraphicsRectItem::Type)) {
      this->setCursor(Qt::SizeAllCursor);
    } else {
      this->setCursor(Qt::ArrowCursor);
    }

    if (this->movingitem && this->mousepressed) { // move the control point
      int x = p.x();
      int y = p.y();

      if (x > (this->size - 1) - this->ptsize) x = (this->size - 1) - this->ptsize;
      if (y > (this->size - this->ptsize)) y = this->size  - this->ptsize;
      if (x < this->ptsize) x = this->ptsize;
      if (y < this->ptsize) y = this->ptsize;

      this->movingitem->moveBy(x - movingstart.x(), y - movingstart.y());
      this->movingstart = QPoint(x, y);
      this->updateCurve();
    }
  } else { // draw a color mapping
    if (this->mousepressed) {
      int lastx = lastpos.x();
      int lasty = lastpos.y();
      int currentx = p.x();
      int currenty = p.y();

      if ((lastx >= 0) && (lastx <= (this->size - 1)) &&
          (currentx >= 0) && (currentx <= (this->size - 1))) {

        if (currentx < lastx) { // swap
          currentx ^= lastx ^= currentx ^= lastx;
          currenty ^= lasty ^= currenty ^= lasty;
        }
        float x0 = float(lastx);
        float y0 = float(lasty);
        float x1 = float(currentx);
        float y1 = float(currenty);
        float dx = x1 - x0;

        // fill in the points between p and lastpos,
        // linearly interpolate the position
        for (int i = lastx; i < currentx; i++) {
          float w0 = (x1 - float(i)) / dx;
          float w1 = (float(i) - x0) / dx;
          int y = int(w0 * y0 + w1 * y1 + 0.5f);
          // clamp
          if (y > (this->size - 1)) y = (this->size - 1);
          if (y < 0) y = 0;
          this->colorcurves[this->colorindex]->setColorMapping(i, (this->size - 1)-y);
        }
        this->lastpos = p;
        this->updateCurve();
      }
    }
  }
  this->canvas->update();
}

void
CurveView::drawContents(QPainter * p)
{
  this->drawContents(p, 0, 0, this->sceneRect().width(), this->sceneRect().height());
}

void
CurveView::drawContents(QPainter * p, int cx, int cy, int cw, int ch)
{
  QList<QGraphicsItem*>::Iterator it;

    // draw the grid in the background
  it = this->grid.begin();
  for (; it != this->grid.end(); it++) {
      (*it)->update();// paint(p);
  }
  // draw the curve
  it = this->curvesegments.begin();
  for (; it != this->curvesegments.end(); it++) {
    (*it)->update();//paint(p);
  }
  // draw the control points
  if (this->curvemode == CurveView::SMOOTH) {
    it = this->canvasctrlpts[this->colorindex].begin();
    for (; it != this->canvasctrlpts[this->colorindex].end(); ++it) {
        (*it)->update();//paint(p);
    }
  }
}

void
CurveView::hideUnselected()
{
  QList<QGraphicsItem*>::Iterator it;

  for (int i = 0; i < this->colormode; i++) {
    it = this->canvasctrlpts[i].begin();
    for (; it != this->canvasctrlpts[i].end(); ++it) {
      if ((this->colorindex == i) && (this->curvemode != CurveView::FREE)) {
        (*it)->show();
      } else {
        (*it)->hide();
      }
    }
  }
}

void
CurveView::resetActive()
{
  this->colorcurves[this->colorindex]->resetCtrlPoints();
  // QList<QGraphicsItem>::clear() only removes the items from the list,
  // but they need to be deleted also.
  QList<QGraphicsItem*>::Iterator it = this->canvasctrlpts[this->colorindex].begin();
  for (; it != this->canvasctrlpts[this->colorindex].end(); it++) {
    delete (*it);
  }
  this->canvasctrlpts[this->colorindex].clear();
  this->canvasctrlpts[this->colorindex] = this->newCanvasCtrlPtList();
  this->curvemode = CurveView::SMOOTH;
  this->updateCurve();
  this->canvas->update();
}

QList<QGraphicsItem*>
CurveView::newCanvasCtrlPtList()
{
  QList<QGraphicsItem*> list;
  int numpts = this->colorcurves[this->colorindex]->getNumCtrlPoints();
  const SbList<SbVec3f> ctrlpts = this->colorcurves[this->colorindex]->getCtrlPoints();

  for (int i = 0; i < numpts; i++) {
    list.append(this->newControlPoint(int(ctrlpts[i][0] * (this->size - 1)), int((this->size - 1) - ctrlpts[i][1] * (this->size - 1))));
  }
  return list;
}

QGraphicsRectItem *
CurveView::newControlPoint(int x, int y)
{
  QGraphicsRectItem * rect
    = new QGraphicsRectItem(x-this->ptsize, y-this->ptsize,
                           this->ptsize*2, this->ptsize*2);
  rect->setZValue(2); // the control points will be drawn on top of the curve
  rect->show();
  this->canvas->addItem(rect);
  return rect;
}

void
CurveView::updateCurve()
{
  QList<QGraphicsItem*>::iterator it;

  int i = 0;
  if (this->curvemode == CurveView::SMOOTH) {
    QList<QGraphicsItem*> list = this->canvasctrlpts[this->colorindex];
    QList<QGraphicsItem*> sortedlist;

    // Sort the list of control points
    while ((it = list.begin()) != list.end()) {
      QGraphicsRectItem * smallest = (QGraphicsRectItem *) this->smallestItem(&list);
      smallest->setBrush(Qt::black);
      sortedlist.append(smallest);
      list.removeAll(smallest);
    }
    SbList<SbVec3f> ctrlpts;
    for (it =  sortedlist.begin(); it != sortedlist.end(); it++) {
      float x = ((*it)->x() + float(this->ptsize)) / (this->size - 1);
      float y = 1.0f - ((*it)->y() + float(this->ptsize)) / (this->size - 1);
        ctrlpts.append(SbVec3f(x, y, 0.0f));
    }
    this->colorcurves[this->colorindex]->setCtrlPoints(ctrlpts);
  }

  i = 2;
  it = this->curvesegments.begin();
  const uint8_t * curvepts = this->colorcurves[this->colorindex]->getColorMap();
  for (; it != this->curvesegments.end(); it++) {
    QGraphicsLineItem* line = (QGraphicsLineItem*)(*it);
    line->setLine(i-2, int(this->size - 1)-curvepts[i-2], i, int(this->size - 1)-curvepts[i]);
    i+=2;
  }
  emit this->curveChanged();
}

QGraphicsItem *
CurveView::smallestItem(QList<QGraphicsItem*> * list)
{
  QList<QGraphicsItem*>::Iterator it = list->begin();
  QGraphicsItem * smallest = (*it);

  it++;
  for (; it != list->end(); ++it) {
    if ((*it)->x() < smallest->x()) {
      smallest = (*it);
    }
  }
  return smallest;
}

void
CurveView::setMode(SoQtColorTableEditor::Mode mode)
{
  for (int i = 0; i < this->colormode; i++) {
    delete this->colorcurves[i];
    QList<QGraphicsItem*>::Iterator it = this->canvasctrlpts[i].begin();
    for (; it != this->canvasctrlpts[i].end(); it++) {
      delete *it;
    }
  }
  this->colorcurves.truncate(0);
  this->canvasctrlpts.truncate(0);

  this->colormode = mode;
  this->initColorCurves();
  this->hideUnselected();
}

void
CurveView::changeColorMode(int mode)
{
  if (mode != this->colorindex) {
    this->colorindex = mode;
    this->hideUnselected();
    this->updateCurve();
    this->canvas->update();
  }
}

void
CurveView::changeCurveMode(int cmode)
{
  if (cmode != this->curvemode) {
    this->curvemode = (CurveType) cmode;
    if (this->curvemode == CurveView::SMOOTH) {
      this->interpolateFromColors();
    }
    this->hideUnselected();
    this->updateCurve();
    this->canvas->update();
  }
}

void
CurveView::interpolateFromColors()
{
  for (int i = 0; i < this->colormode; i++) {
    this->colorcurves[i]->interpolateColorMapping();
    SbList<SbVec3f> ctrlpts = this->colorcurves[i]->getCtrlPoints();

    QList<QGraphicsItem*>::Iterator it = this->canvasctrlpts[i].begin();
    for (; it != this->canvasctrlpts[i].end(); it++) {
      delete (*it);
    }
    this->canvasctrlpts[i].clear();
    for (int j = 0; j < this->colorcurves[i]->getNumCtrlPoints(); j++) {
      this->canvasctrlpts[i].append(
        this->newControlPoint(int(ctrlpts[j][0] * (this->size - 1)), int((this->size - 1) - ctrlpts[j][1] * (this->size - 1))));
    }
  }
}

void
CurveView::setConstantValue(int value)
{
  this->colorcurves[this->colorindex]->fill(value);
  this->updateCurve();
  this->canvas->update();
}

void
CurveView::getColors(uint8_t * colors, int num) const
{
  uint8_t * clrs = new uint8_t[num];
  for (int i = 0; i < this->colormode; i++) {
    this->colorcurves[i]->getColors(clrs, num);
    for (int j = 0; j < num; j++) {
      colors[j*(this->colormode) + i] = clrs[j];
    }
  }
  delete [] clrs;
}

void
CurveView::setColors(uint8_t * colors, int num)
{
  uint8_t * clrs = new uint8_t[num];
  for (int i = 0; i < colormode; i++) {
    for (int j = 0; j < num; j++) {
      clrs[j] = colors[j*colormode + i];
    }
    this->colorcurves[i]->setColors(clrs, num);
  }
  delete [] clrs;
  this->changeCurveMode(CurveView::FREE);
}

QPixmap
CurveView::getPixmap(int width, int height) const
{
  QImage img(width, height, QImage::Format_ARGB32_Premultiplied);
  QPixmap pm;
  if (this->colormode < 3) {
    const uint8_t * colors = this->colorcurves[0]->getColorMap();
    pm = this->makePixmap(width, height, colors, colors, colors);
  } else {
    const uint8_t * red = this->colorcurves[0]->getColorMap();
    const uint8_t * green = this->colorcurves[1]->getColorMap();
    const uint8_t * blue = this->colorcurves[2]->getColorMap();
    pm = this->makePixmap(width, height, red, green, blue);
  }
  return pm;
}

QPixmap
CurveView::makePixmap(int w, int h, const uint8_t * r, const uint8_t * g, const uint8_t * b) const
{
  // use an image since it is optimized for direct pixel access
  QImage img(w, h, QImage::Format_ARGB32_Premultiplied);
  for (int i = 0; i < w; i++) {
    int org = (int) ((float(i) / float(w)) * (this->size - 1));
    for (int j = 0; j < h; j++) {
      img.setPixel(i, j, qRgb(r[i], g[i], b[i]));
    }
  }
  return QPixmap::fromImage(img);
}

// just a convenient method used to get the vertical gradient
// that indicates the y-axis
QPixmap
CurveView::getGradient(int width, int height) const
{
  QImage img(width, height, QImage::Format_ARGB32_Premultiplied);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      img.setPixel(j, i, qRgb((this->size - 1)-i, (this->size - 1)-i, (this->size - 1)-i));
    }
  }
  return QPixmap::fromImage(img);
}

void
CurveView::setCallBack(ColorCurve::ChangeCB * cb, void * userData)
{
  for (int i = 0; i < this->colormode; i++) {
    this->colorcurves[i]->setChangeCallBack(cb, userData);
  }
}
