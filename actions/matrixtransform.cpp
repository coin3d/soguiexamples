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

// This example converts all SoMatrixTransform nodes in the scenegraph
// into SoTransform nodes.

#include <Inventor/SoDB.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>


int
main(int argc, char ** argv)
{
  SoDB::init();

  if (argc != 2) {
    (void)fprintf(stderr, "\nUsage: %s <filename.iv>\n\n", argv[0]);
    exit(1);
  }

  SoInput input;
  SbBool ok = input.openFile(argv[1]);
  if (!ok) { exit(1); }

  SoSeparator * root = SoDB::readAll(&input);
  if (root == NULL) { exit(1); }
  root->ref();

  SoSearchAction searchaction;
  searchaction.setType(SoMatrixTransform::getClassTypeId(), FALSE);
  searchaction.setSearchingAll(TRUE);
  searchaction.setInterest(SoSearchAction::ALL);
  searchaction.apply(root);

  SoPathList & pathlist = searchaction.getPaths();
  int len = pathlist.getLength();
  for (int i=0; i < len; i++) {
    SoMatrixTransform * mt = (SoMatrixTransform *)pathlist[i]->getTail();
    assert(mt->isOfType(SoMatrixTransform::getClassTypeId()));
    SbMatrix matrix = mt->matrix.getValue();

    SoGroup * parent = (SoGroup *)pathlist[i]->getNodeFromTail(1);
    assert(parent->isOfType(SoGroup::getClassTypeId()));

    int idx = parent->findChild(mt);
    assert(idx != -1);
    parent->removeChild(idx);

    SbVec3f translation;
    SbRotation rotation;
    SbVec3f scalevec;
    SbRotation scaleorientation;
    matrix.getTransform(translation, rotation, scalevec, scaleorientation);

    SoTransform * transform = new SoTransform;
    transform->translation = translation;
    transform->rotation = rotation;
    transform->scaleFactor = scalevec;
    transform->scaleOrientation = scaleorientation;
    parent->insertChild(transform, idx);
  }

  SoWriteAction writeaction;
  writeaction.apply(root);

  root->unref();
  return 0;
}
