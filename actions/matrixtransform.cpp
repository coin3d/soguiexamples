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
