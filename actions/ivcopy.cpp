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

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/actions/SoWriteAction.h>

#define IVCOPY_USAGE \
  "Usage: %s [-b] <input-file> [<output-file>]\n"

// TODO: when zlib-compression is implemented, add support for writing with
// compression enabled.  Use 'tar' letters: z = libz, j = bzip2.  Only enable
// when building against Coin-2...
// 
// New usage string: "Usage: %s [-bjz] <input-file> [<output-file>]\n"

int
main(int argc, char ** argv)
{
  int optoffset = 0;
  int binary = FALSE;

  if ( argc < 2 ) {
    fprintf(stderr, IVCOPY_USAGE, argv[0]);
    return 0;
  }

  if ( strcmp(argv[1], "-b") == 0 ) {
    optoffset++;
    binary = TRUE;
    if ( argc < 3 ) {
      fprintf(stderr, IVCOPY_USAGE, argv[0]);
      return 0;
    }
  }

  SoDB::init();

  SoInput input;
  if ( !input.openFile(argv[1+optoffset]) ) {
    // err msg comes from SoInput::openFile()
    return 1;
  }

  SoSeparator * root = SoDB::readAll(&input); 
  if ( root == NULL ) {
    // err msg comes from SoDB::readAll()
    return 1;
  }
  root->ref();

  FILE * out = stdout;
  if ( argc == (3+optoffset) ) {
    out = fopen(argv[2+optoffset], "wb+");
    if ( !out ) {
      root->unref();
      fprintf(stderr, "%s: unable to open '%s' for writing.\n", argv[0], argv[2+optoffset]);
      return 1;
    }
  }
  
  SoOutput output;
  output.setFilePointer(out);
  if ( binary ) output.setBinary(TRUE);

  SoWriteAction * writer = new SoWriteAction(&output);
  writer->apply(root);

  delete writer;
  root->unref();

  return 0;
}
