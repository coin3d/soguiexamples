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

/* First submitted in a competition entry by Marius Bugge Monsen.
   Cleaned up and submitted as commonly available code by Marius
   Kintel. */

#ifndef SOGUIEXAMPLES_TEXTUREWRITER_H
#define SOGUIEXAMPLES_TEXTUREWRITER_H

#include <Inventor/SbString.h>

class TextureWriter
{
  unsigned int numCols;
  unsigned int numLines;
  unsigned int fontXSize;
  unsigned int fontYSize;
  unsigned int texXSize;
  unsigned int texYSize;

  char *buffer;
  unsigned int *texture;
  unsigned int color;
  unsigned int background;
  unsigned int column;
  unsigned int line;

  // render character to pixelbuffer
  void render(char c, unsigned int line, unsigned int column);
public:

  TextureWriter(unsigned int cols, unsigned int lines);
  ~TextureWriter();                   // destructor
  void out(SbString& string);       // output string
  void out(const char *string);     // output string
  void out(const char c);           // output char
  void nl();                        // newline
  void back();                      // remove previous char
  void render();                    // render charbuffer to pixelbuffer
  void cursor();                    // update cursor
  void setTextColor(unsigned char r,unsigned char g,unsigned char b,
                    unsigned char a);
  void setBackgroundColor(unsigned char r,unsigned char g,unsigned char b,
                          unsigned char a);
  float getAspectRatio();            // w/h
  void *getTexture();                // get pixelbuffer
  int getTextureXSize() {return this->texXSize;}
  int getTextureYSize() {return this->texYSize;}
};

#endif // !SOGUIEXAMPLES_TEXTUREWRITER_H
