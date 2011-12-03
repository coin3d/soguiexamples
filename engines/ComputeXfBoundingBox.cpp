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

// An engine for calculating and returning the real corner points of a
// 3D bounding box.
//
// (The Coin library's built-in engine SoComputeBoundingBox projects
// the bounding box to be aligned with the world coordinate system's
// principal axes before outputting it.)

#include <ComputeXfBoundingBox.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/SoLists.h>

SO_ENGINE_SOURCE(ComputeXfBoundingBox);

/*!
  \var SoSFNode ComputeXfBoundingBox::node

  If this input field is set and ComputeXfBoundingBox::path is \c
  NULL, the resultant bounding box will be the box encompassing the
  scene graph rooted at this node pointer.
*/
/*!
  \var SoSFPath ComputeXfBoundingBox::path

  If this input field is not \c NULL, the bounding box values of the
  given path will be set on the outputs.
*/
/*!
  \var SoEngineOutput ComputeXfBoundingBox::corners

  (SoMFVec3f) Contains all eight corner coordinates of the bounding
  box.

  They are ordered as follows: bottom back left, bottom back right,
  bottom front right, bottom front left, top front left, top front
  right, top back right, top back left.
*/


ComputeXfBoundingBox::ComputeXfBoundingBox(void)
{
  SO_ENGINE_CONSTRUCTOR(ComputeXfBoundingBox);

  SO_ENGINE_ADD_INPUT(node,(NULL));
  SO_ENGINE_ADD_INPUT(path,(NULL));

  SO_ENGINE_ADD_OUTPUT(corners, SoMFVec3f);

  // Start with a default viewportregion.
  this->bboxaction = new SoGetBoundingBoxAction(SbViewportRegion());
}

void
ComputeXfBoundingBox::initClass(void)
{
  SO_ENGINE_INIT_CLASS(ComputeXfBoundingBox, SoEngine, "SoEngine");
}

ComputeXfBoundingBox::~ComputeXfBoundingBox()
{
  delete this->bboxaction;
}

void
ComputeXfBoundingBox::evaluate(void)
{
  SoPath * bboxpath = this->path.getValue();
  SoNode * bboxnode = this->node.getValue();

  if (!bboxpath && !bboxnode) { return; }

  if (bboxpath) this->bboxaction->apply(bboxpath);
  else this->bboxaction->apply(bboxnode);

  SbXfBox3f xfbox = this->bboxaction->getXfBoundingBox();

  float ox, oy, oz;
  xfbox.getOrigin(ox, oy, oz);
  SbVec3f org(ox, oy, oz);
  float dx, dy, dz;
  xfbox.getSize(dx, dy, dz);

  SbVec3f xv(dx, 0.0f, 0.0f);
  SbVec3f yv(0.0f, dy, 0.0f);
  SbVec3f zv(0.0f, 0.0f, dz);

  SbMatrix t = xfbox.getTransform();

  t.multVecMatrix(org, org);
  t.multDirMatrix(xv, xv);
  t.multDirMatrix(yv, yv);
  t.multDirMatrix(zv, zv);

  SbVec3f veccorners[] = {
    // bottom quad
    org, // back left
    org + xv, // back right
    org + xv + zv, // front right
    org + zv, // front left

    // top quad
    org + yv + zv, // front left
    org + yv + zv + xv, // front right
    org + yv + xv, // back right
    org + yv, // back left
  };

  SO_ENGINE_OUTPUT(corners, SoMFVec3f, setValues(0, 8, veccorners));
}

void
ComputeXfBoundingBox::setViewportRegion(const SbViewportRegion & vpr)
{
  this->bboxaction->setViewportRegion(vpr);
}

const SbViewportRegion &
ComputeXfBoundingBox::getViewportRegion(void) const
{
  return this->bboxaction->getViewportRegion();
}
