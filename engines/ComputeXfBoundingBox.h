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

#ifndef SOGUIEXAMPLES_SOCOMPUTEBOUNDINGBOX_H
#define SOGUIEXAMPLES_SOCOMPUTEBOUNDINGBOX_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/engines/SoEngineOutput.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFPath.h>
#include <Inventor/SbViewportRegion.h>

class SoGetBoundingBoxAction;


class ComputeXfBoundingBox : public SoEngine {
  typedef SoEngine inherited;

  SO_ENGINE_HEADER(ComputeXfBoundingBox);

public:
  SoSFNode node;
  SoSFPath path;

  SoEngineOutput corners;  // SoMFVec3f

  ComputeXfBoundingBox(void);
  static void initClass(void);

  void setViewportRegion(const SbViewportRegion & vpr);
  const SbViewportRegion & getViewportRegion(void) const;

protected:
  virtual ~ComputeXfBoundingBox();
  virtual void evaluate(void);

private:
  SoGetBoundingBoxAction * bboxaction;
};

#endif // !SOGUIEXAMPLES_SOCOMPUTEBOUNDINGBOX_H
