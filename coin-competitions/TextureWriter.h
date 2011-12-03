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
  void render(int c, unsigned int line, unsigned int column);
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
