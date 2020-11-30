#ifndef GRADIENT_H
#define GRADIENT_H

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

#include <qcolor.h>
#include <QTextStream>
#include <Inventor/SbBasic.h>

// *************************************************************************

class Gradient {

public:
  Gradient(const QColor & color0 = Qt::red, const QColor & color1 = Qt::blue);
  Gradient(const Gradient & grad);
  Gradient(const QString & filename);

  ~Gradient();

  unsigned int numTicks(void) const;
  unsigned int insertTick(float t);
  float getParameter(unsigned int i) const;
  SbBool leftEqualsRight(unsigned int i) const;
  QRgb eval(float t) const;

  enum TickSide { LEFT, RIGHT };
  QRgb getColor(unsigned int i, TickSide s) const;
  void setColor(unsigned int i, TickSide s, const QRgb & color);

  void moveTick(unsigned int i, float t);
  void removeTick(unsigned int i);

  void getColorArray(QRgb * colors, unsigned int num) const;
  void save(const QString & filename) const;
  void load(const QString & filename);
  void load(QTextStream & stream);

  QImage getImage(unsigned int w, unsigned int h, QImage::Format fmt) const;

  Gradient & operator = (const Gradient & grad);
  SbBool operator == (const Gradient & grad) const;

  typedef void ChangeCB(const Gradient & grad, void * userdata);
  void setChangeCallback(Gradient::ChangeCB * callBack, void * userdata);
  
private:
  class GradientP * pimpl;
};

#endif // ! GRADIENT_H
