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
