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

/*!
  \class GradientView GradientView.h
  \brief The GradientView class wraps a Gradient in UI controls.
  \ingroup components

  Provides visualization of and controls on a Gradient object. The UI
  controls makes it possible to change the color values of the
  underlying gradient.
*/

// FIXME: I wonder if this shouldn't rather just have been a class for
// displaying a gradient, and the actual UI controls better be placed
// in the GradientEditor class. Discuss with frodo. 20031008 mortene.

// *************************************************************************

#include <stdlib.h>
#include <assert.h>

#include <qimage.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qvaluelist.h>
#include <qpopupmenu.h>
#include <qcolordialog.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qstatusbar.h>

#include "Gradient.h"
#include "GradientView.h"
#include "TickMark.h"
#include "ImageItem.h"
#include "moc_GradientView.icc"

// *************************************************************************

GradientView::GradientView(QCanvas * c,
                           const Gradient & g,
                           QWidget * parent,
                           const char * name,
                           WFlags f)
                           
  : QCanvasView(c, parent, name, f)
{
  this->canvas = c;
  this->canvas->resize(this->sizeHint().width(),
                       this->sizeHint().height());

  this->setMinimumHeight(75);
  this->setMaximumHeight(100);
  this->grad = g;
  this->graditem = NULL;
  this->selectionmarker = NULL;
  this->currenttick = -1;
  this->menu = NULL;
  this->segmentidx = 0;
  this->mousepressed = FALSE;
  this->min = 0;
  this->max = 255;

  QVBoxLayout * topLayout = new QVBoxLayout(this);
  topLayout->setAlignment(Qt::AlignBottom);
  this->statusbar = new QStatusBar(this);
  this->statusbar->setSizeGripEnabled(FALSE);
  this->selectionmarker = new ImageItem(this->canvas);
  this->graditem = new ImageItem(this->canvas);
  this->graditem->show();

  topLayout->addWidget(this->statusbar);

  connect(this, SIGNAL(viewChanged()), this, SLOT(updateView()));
  connect(this, SIGNAL(ticksChanged()), this, SLOT(updateTicks()));

  this->viewport()->setMouseTracking(TRUE);
  this->updateTicks();
  emit this->viewChanged();
}

GradientView::~GradientView()
{
  delete this->graditem;
  delete this->selectionmarker;
  delete this->canvas;
  delete this->menu;
}

QSize
GradientView::sizeHint() const
{
  return QSize(450, 75);
}

void
GradientView::viewportResizeEvent(QResizeEvent * e)
{
  this->canvas->resize(e->size().width(), e->size().height());
  this->updateTicks();
  emit this->viewChanged();
}

void
GradientView::updateView(void)
{
  const int width = this->canvas->width();
  const int height = this->canvas->height();

  int h = this->statusbar->height();
  const QImage gradImage = this->grad.getImage(width, height-10-h, 32);
  this->graditem->setImage(gradImage);
  // FIXME: tell the graditem to redraw all of itself
  // not just those parts that have been touched by another item
  // in a more elegant way. 20030910 frodo
  this->graditem->setVisible(FALSE);
  this->graditem->setVisible(TRUE);

  if (this->segmentidx != -1) {
    const int selectstart = (int) (this->tickmarks[this->segmentidx]->x());
    const int selectend = (int) (this->tickmarks[this->segmentidx + 1]->x());
  
    QImage selectedimage(selectend - selectstart, 10, 32);
    selectedimage.fill(QColor(100,100,245).rgb());
    
    this->selectionmarker->setImage(selectedimage);
    this->selectionmarker->move(selectstart, height-10-h);
    this->selectionmarker->setZ(2);
    this->selectionmarker->show();
  }
  else {
    this->selectionmarker->hide();
  }

  this->canvas->update();
}

void
GradientView::contentsMousePressEvent(QMouseEvent * e)
{
  QPoint p = inverseWorldMatrix().map(e->pos());
 
  switch (e->button()) {
  case Qt::LeftButton:
    {
      this->mousepressed = TRUE;
      this->unselectAll();

      this->currenttick = -1;
      this->segmentidx = -1;

      const unsigned int nrticks = this->tickmarks.size();
      for (unsigned int idx = 0; idx < nrticks; idx++) {
        if (this->tickmarks[idx]->x() < p.x()) { this->segmentidx++; }

        // We don't want it to be possible to pick up the invisible
        // first and last (left and right border) tickmarks.
        if (idx == 0) continue;
        if (idx == nrticks - 1) continue;

        if (this->tickmarks[idx]->hit(p)) {
          this->moving_start = p;
          this->currenttick = idx;
          this->segmentidx = -1;
          this->tickmarks[idx]->setBrush(Qt::blue);
          break; // only one tick mark should be selected (and blue) at a time
        }
      }
      emit this->viewChanged();
    }
    break;

  case Qt::RightButton: 
    if ((this->currenttick != -1) || (this->segmentidx != -1)) {
      this->buildMenu();
      if (this->menu->exec(e->globalPos())) {
        // FIXME: this seems unnecessary. 20031008 mortene.
        delete this->menu;
        this->menu = NULL;
      }
    }
    break;

  default: // do nothing
    break;
  }
}

void
GradientView::contentsMouseReleaseEvent(QMouseEvent * e)
{
  this->mousepressed = FALSE;
}

void
GradientView::contentsMouseMoveEvent(QMouseEvent * e)
{
  if (this->mousepressed) {
    if (this->currenttick == -1) { return; }
    QPoint p = inverseWorldMatrix().map(e->pos());
    int x = p.x();

    assert(this->currenttick > 0);
    assert(this->currenttick < (int)(this->tickmarks.size() - 1));

    TickMark * left = this->tickmarks[this->currenttick - 1];
    TickMark * current = this->tickmarks[this->currenttick];
    TickMark * right = this->tickmarks[this->currenttick + 1];

    const int movex = x - this->moving_start.x();
    const int newpos = (int) (current->x() + movex);
    
    if ((newpos >= left->x()) && newpos <= right->x()) {
      current->moveBy(movex, 0);
      
      this->moving_start = QPoint(x, p.y());
      
      const float t = current->getPos();
      this->grad.moveTick(this->currenttick, t);

      const float value = t * (this->max - this->min) + 0.5f;
      QString s;
      s.sprintf("Color table index: %d", (int)(value + 0.5f));
      this->statusbar->message(s);
      
      emit this->viewChanged();
    }
  } else {
    QPoint p = inverseWorldMatrix().map(e->pos());
    float t = (float)p.x() / (float)this->canvas->width();
    // this test should not be necessary, however the mouse coordinates from
    // the mouse event can sometimes be out of bounds, i.e. they can sometimes
    // be smaller than 0 or larger than canvas.width or canvas.height.
    if ((t >= 0.0f) && (t <= 1.0f)) {
      QRgb col = this->grad.eval(t);
      QString s;
      s.sprintf("RGBA: 0x%02x%02x%02x%02x", qRed(col), qGreen(col), qBlue(col), qAlpha(col));
      this->statusbar->message(s);
    }
  }
}

void
GradientView::unselectAll(void)
{
  QValueList<TickMark*>::Iterator it = this->tickmarks.begin();
  for (; it != tickmarks.end(); ++it) {
    (*it)->setBrush(Qt::black);
  }
  this->currenttick = -1;
}

void
GradientView::setGradient(const Gradient & grad)
{
  this->grad = grad;
  this->currenttick = -1;
  this->segmentidx = -1;
  this->updateTicks();
  emit this->viewChanged();
}

void
GradientView::setDataLimits(float min, float max)
{
  this->min = min;
  this->max = max;
}

const Gradient &
GradientView::getGradient(void) const
{
  return this->grad;
}

void
GradientView::centerTick(void)
{
  assert(this->currenttick > 0);
  assert(this->currenttick < (int)(this->tickmarks.size() - 1));

  const double left = this->tickmarks[this->currenttick - 1]->x();
  const double right = this->tickmarks[this->currenttick + 1]->x();
  const double center = (right - left) / 2.0 + left;

  this->grad.moveTick(this->currenttick, center / this->canvas->width());

  this->updateTicks();
  emit this->viewChanged();
}

TickMark *
GradientView::newTick(int x)
{
  TickMark* i = new TickMark(this->canvas);
  i->setBrush(QColor(0,0,0));
  i->move(0, this->canvas->height()-15-this->statusbar->height());
  i->setZ(3);
  i->setX(x);
  i->show();
  return i;
}

void
GradientView::insertTick(void)
{
  assert(this->segmentidx != -1);
  const float selectStart = this->tickmarks[this->segmentidx]->x();
  const float selectEnd = this->tickmarks[this->segmentidx + 1]->x();

  // x == midpoint of selected section
  const float x = ((selectEnd - selectStart)/2.0f + selectStart);

  const float t = x / (float)this->canvas->width();
  const int i = this->grad.insertTick(t);

  QValueList<TickMark*>::Iterator it = this->tickmarks.begin();
  // the += operator wasn't available until Qt 3.1.0. Just iterate
  // and use ++. pederb, 2003-09-22
  for (int j = 0; j < i; j++) { it++; }
  this->tickmarks.insert(it, this->newTick((int) x));

  this->segmentidx = -1;

  emit this->viewChanged();
}

// FIXME: this is _not_ good design -- it's potentially inefficient
// and bugridden. As an example, consider the synchronization problem
// if some other code adds or removes tickmarks in the Gradient
// object.
//
// We should probably rather just let the tickmarks be stored
// canonically in the Gradient class, and set up what we need to do
// around in the GradientView code on demand.
//
// 20031008 mortene.
void
GradientView::updateTicks(void)
{
  QValueList<TickMark*>::Iterator it = this->tickmarks.begin();
  for (; it != tickmarks.end(); ++it) { delete (*it); }

  this->tickmarks.clear();

  for (unsigned int i = 0; i < this->grad.numTicks(); i++) {
    float t = this->grad.getParameter(i);
    int x = (int) (t * (float)this->canvas->width() + 0.5f);
    TickMark * tick = this->newTick(x);
    this->tickmarks.append(tick);
  }
  this->tickmarks[0]->setVisible(FALSE);
  this->tickmarks[this->tickmarks.size()-1]->setVisible(FALSE);
}

// *************************************************************************

void
GradientView::setGradientColor(unsigned int tickmarkidx, Gradient::TickSide side, QRgb col)
{
  this->grad.setColor(tickmarkidx, side, col);
  emit this->viewChanged();
}

void
GradientView::setGradientColor(unsigned int tickmarkidx, Gradient::TickSide side)
{
  const QRgb initial = this->grad.getColor(tickmarkidx, side);
  const QRgb newcol = QColorDialog::getRgba(initial);
  if (newcol != initial) {
    this->setGradientColor(tickmarkidx, side, newcol);
  }
}

void
GradientView::deleteTick(void)
{
  assert(this->currenttick > 0);
  assert(this->currenttick < (int)(this->tickmarks.size() - 1));

  this->grad.removeTick(this->currenttick);
  this->updateTicks();
  this->segmentidx = -1;
  this->mousepressed = FALSE;
  emit this->viewChanged();
}

void
GradientView::copySegmentColorRight(void)
{
  this->setGradientColor(this->segmentidx + 1, Gradient::LEFT,
                         this->grad.getColor(this->segmentidx + 1, Gradient::RIGHT));
}

void
GradientView::copySegmentColorLeft(void)
{
  this->setGradientColor(this->segmentidx, Gradient::RIGHT,
                         this->grad.getColor(this->segmentidx, Gradient::LEFT));
}

void
GradientView::chooseSegmentColorLeft(void)
{  
  this->setGradientColor(this->segmentidx, Gradient::RIGHT);
}

void
GradientView::chooseSegmentColorRight(void)
{  
  this->setGradientColor(this->segmentidx + 1, Gradient::LEFT);
}

void
GradientView::chooseTickColorLeft(void)
{  
  this->setGradientColor(this->currenttick, Gradient::LEFT);
}

void
GradientView::chooseTickColorRight(void)
{  
  this->setGradientColor(this->currenttick, Gradient::RIGHT);
}

void
GradientView::copyTickColorLeft(void)
{  
  this->setGradientColor(this->currenttick, Gradient::RIGHT,
                         this->grad.getColor(this->currenttick, Gradient::LEFT));
}

void
GradientView::copyTickColorRight(void)
{  
  this->setGradientColor(this->currenttick, Gradient::LEFT,
                         this->grad.getColor(this->currenttick, Gradient::RIGHT));
}

// *************************************************************************

// FIXME: callback is not really used from this class, just passed on
// to the Gradient class. Should look into design to see if we can
// remove this method. 20031008 mortene.
void
GradientView::setChangeCallback(Gradient::ChangeCB * cb, void * userdata)
{
  this->grad.setChangeCallback(cb, userdata);
}

// *************************************************************************

void
GradientView::buildMenu(void)
{
  // FIXME: instead of building the menu each time, simply use
  // QPopupMenu::changeItem to change the color pixmaps. 20030925 frodo.
  assert(!this->menu);
  this->menu = new QPopupMenu(this);

  int id;

  // FIXME: use menu titles. 20031008 mortene.
  
  if (this->segmentidx != -1) {
    QPixmap pm(16,16);
    pm.fill(this->grad.getColor(this->segmentidx, Gradient::RIGHT));
    id = menu->insertItem(pm, "Change left-side color", this, SLOT(chooseSegmentColorLeft()));

    pm.fill(grad.getColor(this->segmentidx, Gradient::LEFT));
    id = menu->insertItem(pm, "Copy color from left neighbor", this, SLOT(copySegmentColorLeft()));
    if (this->grad.leftEqualsRight(this->segmentidx)) menu->setItemEnabled(id, FALSE);

    menu->insertSeparator();

    pm.fill(this->grad.getColor(this->segmentidx + 1, Gradient::LEFT));
    id = menu->insertItem(pm, "Change right-side color", this, SLOT(chooseSegmentColorRight()));

    pm.fill(this->grad.getColor(this->segmentidx + 1, Gradient::RIGHT));
    id = menu->insertItem(pm, "Copy color from right neighbor", this, SLOT(copySegmentColorRight()));
    if (this->grad.leftEqualsRight(this->segmentidx + 1)) menu->setItemEnabled(id, FALSE);

    menu->insertSeparator();

    id = menu->insertItem("Insert new tick", this, SLOT(insertTick()));
  }
  else if (this->currenttick != -1) {
    QPixmap pm(16,16);
    pm.fill(this->grad.getColor(this->currenttick, Gradient::LEFT));
    (void)menu->insertItem(pm, "Change left color", this, SLOT(chooseTickColorLeft()));

    pm.fill(this->grad.getColor(this->currenttick, Gradient::RIGHT));
    (void)menu->insertItem(pm, "Change right color", this, SLOT(chooseTickColorRight()));

    menu->insertSeparator();

    const bool lefteqright = this->grad.leftEqualsRight(this->currenttick);

    pm.fill(this->grad.getColor(this->currenttick, Gradient::LEFT));
    id = menu->insertItem(pm, "Copy left color to right", this, SLOT(copyTickColorLeft()));
    if (lefteqright) { menu->setItemEnabled(id, FALSE); }

    pm.fill(this->grad.getColor(this->currenttick, Gradient::RIGHT));
    id = menu->insertItem(pm, "Copy right color to left", this, SLOT(copyTickColorRight()));
    if (lefteqright) { menu->setItemEnabled(id, FALSE); }

    menu->insertSeparator();

    id = menu->insertItem("Delete tick", this, SLOT(deleteTick()));
    id = menu->insertItem("Center tick", this, SLOT(centerTick()));
  }
}
