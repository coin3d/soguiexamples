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

// This example outputs a vector version of the input iv-file, exactly
// as it renders in a renderarea viewer -- i.e. with the camera(s) and
// light source(s) from the file.
//
// mortene.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/SoDB.h>

// this example requires HardCopy support, and uses Coin-specific
// HarcCopy features as well...
#if !defined(HAVE_HARDCOPY) || !defined(__COIN__)

#include <stdio.h>

int
main(int argc, char ** argv)
{
  (void)fprintf(stdout,
                "\n"
                "This example depends on Coin >= 2.1 specific\n"
                "extensions. This is just an informational\n"
                "message and not the real functionality\n"
                "of the example.\n\n");
  return 1;
}

#else // ! HAVE_HARDCOPY || ! __COIN__

#include <Inventor/SoDB.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/nodekits/SoNodeKit.h>
#include <Inventor/SbViewportRegion.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/SoInput.h>
#include <assert.h>
#include <HardCopy/SoHardCopy.h>
#include <HardCopy/SoVectorizePSAction.h>
#include <HardCopy/SoVectorOutput.h>

// FIXME: the lib inits below are duplicated from components/computils
// -- should rather share the code. 20040204 mortene.

#ifdef HAVE_SIMVOLEON_LIBRARY
#include <VolumeViz/nodes/SoVolumeRendering.h>
#endif // HAVE_SIMVOLEON_LIBRARY

#ifdef HAVE_SMALLCHANGE_LIBRARY
#include <SmallChange/misc/Init.h>
#endif // HAVE_SMALLCHANGE_LIBRARY

void
init_extra_libraries(void)
{
#ifdef HAVE_SMALLCHANGE_LIBRARY
  // It is useful to include and init the SmallChange library, as we
  // can then automatically load iv-files which includes extension
  // nodes, engines, nodekits, etc from SmallChange.
  smallchange_init();
#endif // HAVE_SMALLCHANGE_LIBRARY

#ifdef HAVE_SIMVOLEON_LIBRARY
  // Inits SimVoleon, if available, for the same reason as for
  // SmallChange above.
  SoVolumeRendering::init();
#endif // HAVE_SIMVOLEON_LIBRARY
}

// *************************************************************************

#define BORDER 10.0f

// *************************************************************************

int
main(int argc, char ** argv )
{
  if (argc != 3) {
    (void)fprintf(stderr,
                  "\nUsage: specify an Inventor file as the first argument,\n"
                  "and a postscript filename as the second argument.\n\n");
    exit(1);
  }

  SoDB::init();
  SoNodeKit::init();
  SoInteraction::init();

  init_extra_libraries();
 
  SoInput input;
  SbBool ok = input.openFile(argv[1]);
  if (!ok) { exit(1); }

  SoSeparator * root =  SoDB::readAll(&input);
  if (!root) { exit(1); }

  root->ref();

  SoVectorizePSAction va;
  va.setBackgroundColor(TRUE, SbColor(1.0f, 1.0f, 1.0f));
  
  SoVectorOutput * out = va.getOutput();
  if (!out->openFile(argv[2])) {
    (void)fprintf(stderr,"Unable to open '%s' for writing\n", argv[2]);
    exit(1);
  }

  SbViewportRegion vpr(600, 400);

  SbVec2s vpsize = vpr.getViewportSizePixels();
  float vpratio = ((float)vpsize[0]) / ((float)vpsize[1]); 

  if (vpratio > 1.0f) {
    va.setOrientation(SoVectorizeAction::LANDSCAPE);
    vpratio = 1.0f / vpratio;
  }
  else {
    va.setOrientation(SoVectorizeAction::PORTRAIT);
  }

  va.beginStandardPage(SoVectorizeAction::A4, BORDER);

  // try to fill as much "paper" as possible

  // FIXME: consider making getPageSize() public 
  //SbVec2f size = va.getPageSize();
  SbVec2f size = SbVec2f(210.0f - BORDER*2.0f, 
                         297.0f - BORDER*2.0f);

  float pageratio = size[0] / size[1];
  float xsize, ysize;

  if (pageratio < vpratio) {
    xsize = size[0];
    ysize = xsize / vpratio;
  }
  else {
    ysize = size[1];
    xsize = ysize * vpratio;
  }

  float offx = BORDER + (size[0]-xsize) * 0.5f;
  float offy = BORDER + (size[1]-ysize) * 0.5f;

  va.beginViewport(SbVec2f(offx, offy), SbVec2f(xsize, ysize));
  va.calibrate(vpr);

  fprintf(stdout,"Vectorizing...");
  fflush(stdout);
    
  va.apply(root);
  fprintf(stdout,"done\n");
  fflush(stdout);

  fprintf(stdout,"Creating postscript file (%s)...", argv[2]);
  fflush(stdout);
  va.endViewport();    
  va.endPage();
  out->closeFile();

  fprintf(stdout,"done\n");
  fflush(stdout);

  root->unref();

  return 0;
}

#endif // HAVE_HARDCOPY && __COIN__
