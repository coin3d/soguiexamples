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

#include <Inventor/SbLinear.h>
#include <string.h>
#include <assert.h>

#include "utility.h"

uint8_t *
generate8bitVoxelSet(SbVec3s & dim)
{
  const size_t blocksize = dim[0] * dim[1] * dim[2];
  uint8_t * voxels = new uint8_t[blocksize];
  (void)memset(voxels, 0, blocksize);

  float t = 0;

  while (t < 50) {
    SbVec3f v(sin((t + 1.4234) * 1.9) * sin(t) * 0.45 + 0.5,
              cos((t * 2.5) - 10) * 0.45 + 0.5,
              cos((t - 0.23123) * 3) * sin(t + 0.5) * cos(t) * 0.45 + 0.5);

    assert(v[0] < 1.0f && v[1] < 1.0f && v[2] < 1.0f);
    const int nx = int(dim[0] * v[0]);
    const int ny = int(dim[1] * v[1]);
    const int nz = int(dim[2] * v[2]);

    const int memposition = nz*dim[0]*dim[1] + ny*dim[0] + nx;
    voxels[memposition] = (uint8_t)(255.0 * cos(t));

    t += 0.001;
  }

  return voxels;
}
