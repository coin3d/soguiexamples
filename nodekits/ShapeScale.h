/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion. All rights reserved.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
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
