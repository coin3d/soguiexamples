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

#include "qpointarray.h"
#include "TickMark.h"

TickMark::TickMark(QCanvas * canvas)
: QCanvasPolygon(canvas)
{
  QPointArray pa(3);
  pa[0] = QPoint(-6,15);
  pa[1] = QPoint(6,15);
  pa[2] = QPoint(0,0);
  this->setPoints(pa);
}

TickMark::~TickMark()
{
}

bool TickMark::hit(QPoint p) const
{
  if (this->visible()) {
    if (this->boundingRect().contains(p)) {
      return TRUE;
    }
  }
  return FALSE;
}

float TickMark::getPos() const
{
  return float(this->x()) / ((float)canvas()->width() + 0.5f);
}
