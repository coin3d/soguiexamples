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

// This simple example program uses an SoCallbackAction to tesselate a
// model into a single SoIndexedFaceSet of triangles, then dumps this
// scene on stdout.
//
// It's pretty dumb and useless, except for showing off basic
// SoCallbackAction use.

#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTranslation.h>

#include <cassert>

static SoCoordinate3 * coord3 = NULL;
static SoIndexedFaceSet * ifs = NULL;

static int coord3idx = 0;

#ifdef __COIN__
#include <Inventor/SbBSPTree.h>
static SbBSPTree * bsptree = NULL;
#endif // __COIN__

static int
find_coord3_idx(const SoCoordinate3 * c, const SbVec3f & v)
{
#ifdef __COIN__
  return bsptree->findPoint(v);
#else // __COIN__

  // FIXME: the run-time of this algorithm could quickly get very
  // ugly.. like O(n^2)-time ugly. Use an oct-tree or something to
  // fix. 20011009 mortene.
  int size = c->point.getNum();
  for (int i=0; i < size; i++) {
    if (v == c->point[i]) { return i; }
  }
  return -1; // not found

#endif // ! __COIN__
}

static void
triangle_cb(void * userdata, SoCallbackAction * action,
            const SoPrimitiveVertex * v1,
            const SoPrimitiveVertex * v2,
            const SoPrimitiveVertex * v3)
{
  const SbVec3f vtx[] = { v1->getPoint(), v2->getPoint(), v3->getPoint() };
  const SbMatrix mm = action->getModelMatrix();

  SbVec3f vx[3];
  for (int j=0; j < 3; j++) { mm.multVecMatrix(vtx[j], vx[j]); }

  int32_t indices[] = { -1, -1, -1, -1 };

  for (int i=0; i < 3; i++) {
    int presentidx = find_coord3_idx(coord3, vx[i]);
    if (presentidx == -1) {
      coord3->point.setNum(coord3->point.getNum() + 1);
      coord3->point.set1Value(coord3idx, vx[i]);
      indices[i] = coord3idx;
      coord3idx++;
#ifdef __COIN__
      // add point to BSP tree. The point in the BSP tree will have
      // the same index as the corresponding point in the Coordinate3
      // node, and find_coord3_idx() will return the correct index.
      bsptree->addPoint(vx[i]);
#endif // __COIN__
    }
    else {
      indices[i] = presentidx;
    }
  }

  int oldsize = ifs->coordIndex.getNum();
  ifs->coordIndex.setNum(oldsize + 4);
  ifs->coordIndex.setValues(oldsize, 4, indices);
}


int
main(int argc, char ** argv)
{
  if (argc != 2) {
    (void)fprintf(stderr, "\nSpecify an Inventor file as argument.\n");
    return 1;
  }

  SoDB::init();

  SoInput * input = new SoInput;
  if (!input->openFile(argv[1])) { return 1; } // err msg from SoInput::openFile()

  SoSeparator * root = SoDB::readAll(input);
  if (root == NULL) { return 1; } // err msg from SoDB::readAll()
  delete input;

  root->ref();

#ifdef __COIN__
  bsptree = new SbBSPTree;
#endif // __COIN__
  coord3 = new SoCoordinate3;
  coord3->point.setNum(0);
  ifs = new SoIndexedFaceSet;
  ifs->coordIndex.setNum(0);

  SoCallbackAction * ca = new SoCallbackAction;
  ca->addTriangleCallback(SoShape::getClassTypeId(), triangle_cb, NULL);
  ca->apply(root);
  delete ca;

  root->unref();

  SoSeparator * triroot = new SoSeparator;
  triroot->ref();
  triroot->addChild(coord3);
  triroot->addChild(ifs);

  SoWriteAction * wa = new SoWriteAction;
  wa->apply(triroot);
  delete wa;

  triroot->unref();

#ifdef __COIN__
  delete bsptree;
  SoDB::cleanup();
#endif // __COIN__

  return 0;
}
