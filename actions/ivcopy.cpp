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
