/**************************************************************************\
 *
 *  This file is part of a set of example programs for the Coin library.
 *  Copyright (C) 2000-2002 by Systems in Motion. All rights reserved.
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

/*!
  \class ShapeScale ShapeScale.h
  \brief The ShapeScale class is used for scaling a shape based on projected size.

  This nodekit can be inserted in your scene graph to add for instance
  3D markers that will be of a constant projected size.

  The marker shape is stored in the "shape" part. Any kind of node
  can be used, even group nodes with several shapes, but the marker
  shape should be approximately of unit size, and with a center 
  position in (0, 0, 0).
*/

/*!
  \var SoSFFloat ShapeScale::active
  
  Turns the scaling on/off. Default value is TRUE.
*/

/*!
  \var SoSFFloat ShapeScale::projectedSize

  The requested projected size of the shape. Default value is 5.0.
*/

#include "ShapeScale.h"

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>

SO_KIT_SOURCE(ShapeScale);

/*!
  Constructor.
*/
ShapeScale::ShapeScale(void) 
{
  SO_KIT_CONSTRUCTOR(ShapeScale);

  SO_KIT_ADD_FIELD(active, (TRUE));
  SO_KIT_ADD_FIELD(projectedSize, (5.0f));  

#if defined(__COIN__) 
  // the logical (Coin) way to do it. Parts can be initialized in any
  // order.
  SO_KIT_ADD_CATALOG_ENTRY(topSeparator, SoSeparator, FALSE, this, "", FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(scale, SoScale, FALSE, topSeparator, shape, FALSE);
  SO_KIT_ADD_CATALOG_ABSTRACT_ENTRY(shape, SoNode, SoCube, TRUE, topSeparator, "", TRUE);
#else // __COIN__
  // you can also initialize a nodekits like this with Coin, of course,
  // but it's often a pain in the a** to always have to specify the parts
  // that needs to be referenced before it can be referenced as a sibling 
  // of another part.
#define EMPTY \x0 // Inventor doesn't handle "" either
  SO_KIT_ADD_CATALOG_ENTRY(topSeparator, SoSeparator, FALSE, this, EMPTY, FALSE);
  SO_KIT_ADD_CATALOG_ABSTRACT_ENTRY(shape, SoNode, SoCube, TRUE, topSeparator, EMPTY, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(scale, SoScale, FALSE, topSeparator, shape, FALSE);
#undef EMPTY
#endif // ! __COIN__  
  
  SO_KIT_INIT_INSTANCE();
}

/*!
  Destructor.
*/
ShapeScale::~ShapeScale()
{
}

/*!
  Initializes this class. Call before using it.
*/
void
ShapeScale::initClass(void)
{
  SO_KIT_INIT_CLASS(ShapeScale, SoBaseKit, "BaseKit");
}

// FIXME: when using this nodekit in the
// SoGuiExamples/nodekits/scalemarker example, it looks like it
// sometimes doesn't stop sending notifications to the scenegraph --
// causing it to continually trigger redraws.
//
// This is not entirely straightforward to reproduce, but try starting
// and stopping spin animations while having set the envvar
// COIN_SHOW_FPS_COUNTER=1, and you'll sooner or later see that it
// won't stop redrawing even though the scene camera's position and
// orientation is frozen.
//
// 20020630 mortene.


static void 
update_scale(SoScale * scale, const SbVec3f & v)
{
  // only write to field when scaling has changed.
  if (scale->scaleFactor.getValue() != v) {
    scale->scaleFactor = v;
  }
}

// Overridden to (re)initialize scaling before rendering marker.
void 
ShapeScale::GLRender(SoGLRenderAction * action)
{
  SoState * state = action->getState();

  SoScale * scale = (SoScale*) this->getAnyPart(SbName("scale"), TRUE);
  if (!this->active.getValue()) {
    update_scale(scale, SbVec3f(1.0f, 1.0f, 1.0f));
  }
  else {
    const SbViewportRegion & vp = SoViewportRegionElement::get(state);
    const SbViewVolume & vv = SoViewVolumeElement::get(state);
    SbVec3f center(0.0f, 0.0f, 0.0f);
    float nsize = this->projectedSize.getValue() / float(vp.getViewportSizePixels()[1]);
    SoModelMatrixElement::get(state).multVecMatrix(center, center); // transform to WCS
    float scalefactor = vv.getWorldToScreenScale(center, nsize);
    update_scale(scale, SbVec3f(scalefactor, scalefactor, scalefactor));
  }
  inherited::GLRender(action);
}
