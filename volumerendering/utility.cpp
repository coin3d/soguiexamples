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

#include <Inventor/SbLinear.h>
#include <cstring>
#include <cassert>

#include "utility.h"

uint8_t *
generate8bitVoxelSet(SbVec3s & dim)
{
  const size_t blocksize = dim[0] * dim[1] * dim[2];
  uint8_t * voxels = new uint8_t[blocksize];
  (void)memset(voxels, 0, blocksize);

  float t = 0;

  while (t < 50) {
    SbVec3f v((float)sin((t + 1.4234f) * 1.9f) * (float)sin(t) * 0.45f + 0.5f,
              (float)cos((t * 2.5f) - 10) * 0.45f + 0.5f,
              (float)cos((t - 0.23123f) * 3) * (float)sin(t + 0.5f) * (float)cos(t) * 0.45f + 0.5f);

    assert(v[0] < 1.0f && v[1] < 1.0f && v[2] < 1.0f);
    const int nx = int(dim[0] * v[0]);
    const int ny = int(dim[1] * v[1]);
    const int nz = int(dim[2] * v[2]);

    const int memposition = nz*dim[0]*dim[1] + ny*dim[0] + nx;
    voxels[memposition] = (uint8_t)(255.0 * cos(t));

    t += 0.001f;
  }

  return voxels;
}
