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

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <VolumeViz/nodes/SoVolumeRendering.h>
#include <SmallChange/misc/Init.h>

#include "OpaqueChair.h"

int main(int argc, char ** argv)
{

  QWidget *widget = SoQt::init(argc,argv,argv[0]);

  if (argc < 2) {
    printf("Usage: $%s [file]\n", argv[0]);
    exit(0);
  }

  SoSeparator *root = new SoSeparator;
  root->ref();

  // Initialize libraries
  smallchange_init();
  SoVolumeRendering::init();
  SoDB::init();

  // Setup viewer
  SoQtExaminerViewer * eviewer = new SoQtExaminerViewer(widget);
  eviewer->setBackgroundColor(SbColor(0.051,0.051,0.35));
  eviewer->show();

  // Add scenegraph
  OpaqueChair * op = new OpaqueChair(argv[1]);
  SoSeparator * vol = op->getSceneGraph();
  root->addChild(vol);

  SoQt::show(widget);
  eviewer->setSceneGraph(root);
  SoQt::mainLoop();

  SoDB::cleanup();

  return 0;

}
