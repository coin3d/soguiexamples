/**************************************************************************\
 *
 *  This file is part of a set of demo programs for the Coin library.
 *  Copyright (C) 2000-2001 by Systems in Motion. All rights reserved.
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
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
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
  int numCols;
  int numLines;
  int fontXSize;
  int fontYSize;
  int texXSize;
  int texYSize;

  char *buffer;
  unsigned int *texture;
  unsigned int color;
  unsigned int background;
  unsigned int column;
  unsigned int line;

  // render character to pixelbuffer
  void render(char c, unsigned int line, unsigned int column);
public:

  TextureWriter(int cols, int lines); // constructor
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
