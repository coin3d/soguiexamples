/**************************************************************************\
 *
 *  This file is part of a set of example programs for the Coin library.
 *  Copyright (C) 2000-2003 by Systems in Motion. All rights reserved.
 *
 *                   <URL:http://www.coin3d.org>
 *
 *  This sourcecode can be redistributed and/or modified under the
 *  terms of the GNU General Public License version 2 as published by
 *  the Free Software Foundation. See the file COPYING at the root
 *  directory of the distribution for more details.
 *
 *  As a special exception, all sourcecode of the demo examples can be
 *  used for any purpose for licensees of the Coin Professional
 *  Edition License, without the restrictions of the GNU GPL. See our
 *  web pages for information about how to acquire a Professional Edition
 *  License.
 *
 *  Systems in Motion, <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef COIN_SHAPESCALE_H
#define COIN_SHAPESCALE_H
#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFFloat.h>

class SbViewport;
class SoState;
class SbColor;
class SbVec2s;

class ShapeScale : public SoBaseKit {
  typedef SoBaseKit inherited;

  SO_KIT_HEADER(ShapeScale);

  SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);
  SO_KIT_CATALOG_ENTRY_HEADER(scale);
  SO_KIT_CATALOG_ENTRY_HEADER(shape);

public:
  ShapeScale(void);

  static void initClass(void);

public:

  SoSFFloat active;
  SoSFFloat projectedSize;

protected:
  virtual void GLRender(SoGLRenderAction * action);
  virtual ~ShapeScale();
  
private:

};

#endif // ! SHAPESCALE_H
