#ifndef COLORCURVE_H
#define COLORCURVE_H

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

#include <Inventor/SbLinear.h>
#include <Inventor/lists/SbList.h>

class SbGuiCubicSpline;

// *************************************************************************

class ColorCurve {
public:
  enum CurveType { LINEAR, CONSTANT };
  ColorCurve(CurveType type = LINEAR, const int numcolors = 256);
  ~ColorCurve();

  void setColors(uint8_t * colors, int num);
  void getColors(uint8_t * colors, int num) const;

  int getNumColors(void) const;
  int getNumCtrlPoints(void) const;

  void setCtrlPoints(const SbList<SbVec3f> & pts);
  const SbList<SbVec3f> & getCtrlPoints(void) const;
  void resetCtrlPoints(void);

  void setColorMapping(int x, int y);
  const uint8_t * getColorMap(void) const;
  void interpolateColorMapping(void);

  typedef void ChangeCB(void * userdata);
  void setChangeCallBack(ColorCurve::ChangeCB * cb, void * userData);

  void notify(void) const;
  void fill(int value);
  
private:
  void updateColorMap(void);
  void updateCurvePoints(void);
  int eval(float x) const;
  
  CurveType type;

  int prevx;
  const int numcolors;
  const int numpts;
  SbBool needinterpol;
  
  SbVec2f * curvepts;
  uint8_t * colormap;

  SbGuiCubicSpline * curve;
  SbList<SbVec3f> ctrlpts;
  ColorCurve::ChangeCB * callBack;
  void * callbackdata;
};


#endif // COLORCURVE_H
