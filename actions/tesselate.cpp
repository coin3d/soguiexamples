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

#include <assert.h>

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
  // ugly.. like O(n²)-time ugly. Use an oct-tree or something to
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

  SoInput input;
  if (!input.openFile(argv[1])) { return 1; } // err msg from SoInput::openFile()

  SoSeparator * root = SoDB::readAll(&input); 
  if (root == NULL) { return 1; } // err msg from SoDB::readAll()

  root->ref();

#ifdef __COIN__
  bsptree = new SbBSPTree;
#endif // __COIN__
  coord3 = new SoCoordinate3;
  coord3->point.setNum(0);
  ifs = new SoIndexedFaceSet;
  ifs->coordIndex.setNum(0);

  SoCallbackAction ca;
  ca.addTriangleCallback(SoShape::getClassTypeId(), triangle_cb, NULL);
  ca.apply(root);

  root->unref();

  SoSeparator * triroot = new SoSeparator;
  triroot->ref();
  triroot->addChild(coord3);
  triroot->addChild(ifs);

  SoWriteAction wa;
  wa.apply(triroot);

  triroot->unref();

#ifdef __COIN__
  delete bsptree;
#endif __ COIN__

  return 0;
}
