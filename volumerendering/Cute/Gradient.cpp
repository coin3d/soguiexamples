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
#include <qfile.h>
#include <qimage.h>
#include "Gradient.h"

// *************************************************************************

class GradientP {
public:
  GradientP(Gradient * publ);
  unsigned int getColorIndex(unsigned int i, Gradient::TickSide s) const;
  Gradient * pub;
  QList<float> parameters;
  QList<QRgb> colors;
  Gradient::ChangeCB * callBack;
  void * callBackData;
  void copy(const GradientP * p);
};

#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->pub)

// *************************************************************************

GradientP::GradientP(Gradient * publ)
{
  PUBLIC(this) = publ;
}

void
GradientP::copy(const GradientP * p)
{
  this->callBack = p->callBack;
  this->callBackData = p->callBackData;
  this->parameters = p->parameters;
  this->colors = p->colors;
}

unsigned int
GradientP::getColorIndex(unsigned int i, Gradient::TickSide s) const
{
  unsigned int colidx;

  if (i==0 && s==Gradient::LEFT) { colidx = this->colors.size() - 1; } // wrap around
  // there are parameters times two minus one number of colors
  else { colidx = i * 2 - ((s==Gradient::LEFT) ? 1 : 0); }

  if (colidx == this->colors.size()) { colidx = 0; } // wrap around

  assert(colidx < this->colors.size() && "border violation");
  return colidx;
}

Gradient::Gradient(const QColor& color0, const QColor& color1)
{
  this->pimpl = new GradientP(this);
  PRIVATE(this)->callBack = NULL;

  // parameter values will be in the range [0 - 1]
  PRIVATE(this)->parameters.append(0.0f);
  PRIVATE(this)->parameters.append(1.0f);
  PRIVATE(this)->colors.append(color0.rgb());
  PRIVATE(this)->colors.append(color1.rgb());
}

Gradient::Gradient(const Gradient & grad)
{
  this->pimpl = new GradientP(this);
  this->operator=(grad);
}

Gradient::Gradient(const QString & filename)
{
  this->pimpl = new GradientP(this);
  PRIVATE(this)->callBack = NULL;
  this->load(filename);
}

Gradient::~Gradient()
{
}

Gradient &
Gradient::operator=(const Gradient & grad)
{
  PRIVATE(this)->copy(grad.pimpl);
  return *this;
}

SbBool Gradient::operator == (const Gradient & grad) const
{
  return (PRIVATE(this)->parameters == grad.pimpl->parameters) &&
         (PRIVATE(this)->colors == grad.pimpl->colors);
}

QRgb
Gradient::eval(float t) const
{
  assert(t >= 0.0f && t <= 1.0f && "t must be in the interval [0,1]");

  int i = 0;
  // find the interval to evaluate in
  while (PRIVATE(this)->parameters[++i] < t);

  int j = (i-1)*2;

  float t0 = PRIVATE(this)->parameters[i-1];
  float t1 = PRIVATE(this)->parameters[i];

  float dt = t1 - t0;
  assert((dt != 0.0f) && "division by zero");

  // weights for linear interpolation
  float w0 = (t1 - t) / dt;
  float w1 = (t - t0) / dt;

  const QRgb color0 = PRIVATE(this)->colors[j];
  const QRgb color1 = PRIVATE(this)->colors[j+1];

  // add 0.5 to get rounding
  int r = int(w0 * float(qRed(color0)) + w1 * float(qRed(color1)) + 0.5f);
  int g = int(w0 * float(qGreen(color0)) + w1 * float(qGreen(color1)) + 0.5f);
  int b = int(w0 * float(qBlue(color0)) + w1 * float(qBlue(color1)) + 0.5f);
  int a = int(w0 * float(qAlpha(color0)) + w1 * float(qAlpha(color1)) + 0.5f);

  return qRgba(r, g, b, a);
}

unsigned int
Gradient::numTicks(void) const
{
  return PRIVATE(this)->parameters.size();
}

float
Gradient::getParameter(unsigned int i) const
{
  return PRIVATE(this)->parameters[i];
}

void
Gradient::moveTick(unsigned int i, float t)
{
  if ((PRIVATE(this)->parameters[i-1] != t) && PRIVATE(this)->parameters[i+1] != t) {
    PRIVATE(this)->parameters[i] = t;
    if (PRIVATE(this)->callBack) { PRIVATE(this)->callBack(*this, PRIVATE(this)->callBackData); }
  }
}

unsigned int
Gradient::insertTick(float t)
{
  // find position to insert before
  int i = 0;
  QList<float>::Iterator it = PRIVATE(this)->parameters.begin();
  QList<QRgb>::Iterator it2 = PRIVATE(this)->colors.begin();
  // it2 = it * 2 - 1, (+= operator wasn't available until Qt 3.1.0)
  while ((*it) < t) { i++; it++; it2++; it2++; }
  it2--;

  // we use the color of the gradient at this parameter value
  QRgb color = this->eval(t);
  PRIVATE(this)->parameters.insert(it, t);
  it2 = PRIVATE(this)->colors.insert(it2, color);
  PRIVATE(this)->colors.insert(it2, color);

  if (PRIVATE(this)->callBack) { PRIVATE(this)->callBack(*this, PRIVATE(this)->callBackData); }
  return i;
}

void
Gradient::removeTick(unsigned int i)
{
  QList<float>::Iterator it = PRIVATE(this)->parameters.begin();
  QList<QRgb>::Iterator it2 = PRIVATE(this)->colors.begin();
  // the += operator wasn't available until Qt 3.1.0. Just iterate
  // and use ++. pederb, 2003-09-22
  for (unsigned int j = 0; j < i; j++) { it++; it2++; it2++; }
  it2--;

  PRIVATE(this)->parameters.erase(it);
  it2 = PRIVATE(this)->colors.erase(it2);
  PRIVATE(this)->colors.erase(it2);

  if (PRIVATE(this)->callBack) { PRIVATE(this)->callBack(*this, PRIVATE(this)->callBackData); }
}

SbBool
Gradient::leftEqualsRight(unsigned int i) const
{
  i = PRIVATE(this)->getColorIndex(i, Gradient::LEFT);
  unsigned int n = PRIVATE(this)->colors.size();
  return (PRIVATE(this)->colors[i] == PRIVATE(this)->colors[(i+1) % n]);
}

/*!
  See Gradient::getColor() for documentation of input arguments.
*/
void
Gradient::setColor(unsigned int i, TickSide s, const QRgb & color)
{
  i = PRIVATE(this)->getColorIndex(i, s);
  PRIVATE(this)->colors[i] = color;

  if (PRIVATE(this)->callBack) { PRIVATE(this)->callBack(*this, PRIVATE(this)->callBackData); }
}

/*!
  Specify tickmark number for \a i, and either Gradient::LEFT or
  Gradient::RIGHT for \a s to indicate which side of tickmark to read
  the color from.

  Note that tickmark 0 is the invisible tickmark on the far left side,
  and ditto the last tickmark is invisible on the far right side.
*/
QRgb
Gradient::getColor(unsigned int i, TickSide s) const
{
  i = PRIVATE(this)->getColorIndex(i, s);
  return PRIVATE(this)->colors[i];
}

void
Gradient::setChangeCallback(Gradient::ChangeCB * callBack, void * userdata)
{
  PRIVATE(this)->callBack = callBack;
  PRIVATE(this)->callBackData = userdata;
}

void
Gradient::getColorArray(QRgb * colorArray, unsigned int num) const
{
  for (unsigned int i = 0; i < num; i++) {
    float t = float(i) / float(num - 1);
    colorArray[i] = this->eval(t);
  }
}

QImage
Gradient::getImage(unsigned int width, unsigned int height, QImage::Format fmt) const
{
  QImage gradImage(width, height, fmt);
  QRgb * colors = new QRgb[width];
  this->getColorArray(colors, width);

  for (unsigned int i = 0; i < width; i ++) {
    float alpha = float(qAlpha(colors[i])) / 255.0f;
    for (unsigned int j = 0; j < height; j++) {
      // produces a checkerboard pattern of black and white
      QRgb background = 0;
      if (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) {
        background = 255;
      }
      const unsigned char bg = (unsigned char)((1.0f - alpha) * float(background));
      const unsigned char r = (unsigned char)(alpha * float(qRed(colors[i])) + bg);
      const unsigned char g = (unsigned char)(alpha * float(qGreen(colors[i])) + bg);
      const unsigned char b = (unsigned char)(alpha * float(qBlue(colors[i])) + bg);

      gradImage.setPixel(i, j, qRgb(r, g, b));
    }
  }
  delete [] colors;
  return gradImage;
}

void
Gradient::save(const QString & filename) const
{
  QFile outfile(filename);
  if (outfile.open(QIODevice::WriteOnly)) {
    QTextStream stream(&outfile);

    stream << PRIVATE(this)->parameters.size() << " ";

    QList<float>::Iterator it = PRIVATE(this)->parameters.begin();
    for (; it != PRIVATE(this)->parameters.end(); it++) {
      stream << (*it) << " ";

#if 0 // debug
      printf("%f\n", *it);
#endif
    }

    stream << PRIVATE(this)->colors.size() << " ";

    QList<QRgb>::Iterator it2 = PRIVATE(this)->colors.begin();
    for (; it2 != PRIVATE(this)->colors.end(); it2++) {
      stream << (*it2) << " ";

#if 0 // debug
      QRgb rgb = *it2;
      printf("0x%02x 0x%02x 0x%02x 0x%02x\n",
             qRed(rgb), qGreen(rgb), qBlue(rgb), qAlpha(rgb));
#endif
    }
    outfile.close();
  }
}

void
Gradient::load(const QString & filename)
{
  PRIVATE(this)->colors.clear();
  PRIVATE(this)->parameters.clear();

  QFile infile(filename);
  if (infile.open(QIODevice::ReadOnly)) {
    QTextStream stream(&infile);
    this->load(stream);
    infile.close();
  }
  // FIXME: error handling. 20040308 mortene.
}

void
Gradient::load(QTextStream & stream)
{
  // FIXME: proper parsing with error checking. 20040308 mortene.

  PRIVATE(this)->colors.clear();
  PRIVATE(this)->parameters.clear();

  int i;

  int numParameters;
  stream >> numParameters;

  for (i = 0; i < numParameters; i++) {
    float t;
    stream >> t;
    PRIVATE(this)->parameters.append(t);
  }

  int numColors;
  stream >> numColors;

  for (i = 0; i < numColors; i++) {
    QRgb clr;
    stream >> clr;
    PRIVATE(this)->colors.append(clr);
  }
}

#undef PRIVATE
#undef PUBLIC
