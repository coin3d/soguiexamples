/**************************************************************************
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation. See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition license.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#ifndef SOGUIEXAMPLES_COINLOGO_IV_H
#define SOGUIEXAMPLES_COINLOGO_IV_H

// Logo design by Mads Eriksen <mads@sim.no>. Original layout as a
// scenegraph by Marius Bugge Monsen <mariusbu@sim.no>. Submitted to
// SoGuiExamples module by Marius Kintel <kintel@sim.no>.

// Here's a code snippet to show how to use it:
//
//  [...]
//    SoInput in;
//    in.setBuffer((void *)COIN_LOGO, strlen(COIN_LOGO));
//    SoNode * root;
//    SbBool ok = SoDB::read(&in, root);
//    assert(ok && "COIN_LOGO import failed");
//  [...]

// FIXME: this would be better implemented as a SoCoordinate3 and a
// SoIndexedFaceSet.  It works well enough now with a hardcoded font
// for SoText3, but the hardcoded font will eventually be replaced
// with proper dynamic font-loading, and chances are that the
// proportions will be completely wrong on most occasions.
//
// It should be possible to convert the scenegraph to a bunch of
// triangle primitives by applying a SoCallbackAction, I think.
//
// 20010921 mortene.


static const char COIN_LOGO[] =
  "#Inventor V2.1 ascii\n"
  "\n"
  "Separator {\n"
  "  Translation {\n"
  "    translation -2 -2.5 0.2\n"
  "  }\n"
  "  Scale {\n"
  "    scaleFactor 0.6 0.7 0.6\n"
  "  }\n"
  "  Text3 {\n"
  "    string \"C\"\n"
  "    parts (FRONT | SIDES | BACK)\n"
  "  }\n"
  "  Separator {\n"
  "    Translation {\n"
  "      translation 1.75 2.5 0\n"
  "    }\n"
  "    Scale {\n"
  "      scaleFactor 0.57 0.57 1\n"
  "    }\n"
  "    Text3 {\n"
  "      string \"O\"\n"
  "      parts (FRONT | SIDES | BACK)\n"
  "    }\n"
  "    Translation {\n"
  "      translation 2.5 1.1 0\n"
  "    }\n"
  "    Scale {\n"
  "      scaleFactor 0.7 0.7 1\n"
  "    }\n"
  "    Text3 {\n"
  "      string \"I\"\n"
  "      parts (FRONT | SIDES | BACK)\n"
  "    }\n"
  "    Translation {\n"
  "      translation -0.8 -6.3 0\n"
  "    }\n"
  "    Scale {\n"
  "      scaleFactor 0.6 0.6 1\n"
  "    }\n"
  "    Text3 {\n"
  "      string \"N\"\n"
  "      parts (FRONT | SIDES | BACK)\n"
  "    }\n"
  "  }\n"
  "  Translation {\n"
  "    translation 3.6 -0.9 -0.5\n"
  "  }\n"
  "  Scale {\n"
  "    scaleFactor 0.2 0.8 0.5\n"
  "  }\n"
  "  Cube { }\n"
  "  Translation {\n"
  "    translation 0 11.4 0\n"
  "  }\n"
  "  Cube { }\n"
  "}\n";

#endif /* ! SOGUIEXAMPLES_COINLOGO_IV_H */
