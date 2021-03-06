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

/*
 * Class for writing text into a bitmap buffer (to be used as a
 * texture, for instance).
 */

/* First submitted in a competition entry by Marius Bugge Monsen.
   Cleaned up and submitted as commonly available code by Marius
   Kintel. */

#include "TextureWriter.h"
#include "bitmapfont8x12.h"

#include <cstdio>
#include <memory.h>

//FIXME: Datatype for texture?

TextureWriter::TextureWriter(unsigned int cols, unsigned int lines)
{
  this->buffer = new char[cols*lines];
  this->numCols = cols;
  this->numLines = lines;
  this->fontXSize = 8; //FIXME: Support other fontsizes
  this->fontYSize = 12;
  this->texXSize = this->fontXSize*this->numCols;
  this->texYSize = this->fontYSize*this->numLines;
  this->texture = new unsigned int[this->texXSize*this->texYSize];

  memset(this->buffer, 0, cols*lines);
  memset(this->texture, 0, this->texXSize*this->texYSize * 4);

  this->column = 0;
  this->line = 0;

  this->setTextColor(0,0,0,0xff);
  this->setBackgroundColor(0,0,0,0);
}

TextureWriter::~TextureWriter( void )
{
}

void
TextureWriter::setTextColor(unsigned char r,unsigned char g,unsigned char b,
                     unsigned char a)
{
  unsigned char *colptr = (unsigned char *)&this->color;
  colptr[0] = r;
  colptr[1] = g;
  colptr[2] = b;
  colptr[3] = a;
}

void
TextureWriter::setBackgroundColor(unsigned char r,unsigned char g,unsigned char b,
                           unsigned char a)
{
  unsigned char *colptr = (unsigned char *)&this->background;
  colptr[0] = r;
  colptr[1] = g;
  colptr[2] = b;
  colptr[3] = a;
}

void TextureWriter::out(SbString& str)    // output string
{
  this->out(str.getString());
}

void TextureWriter::out( const char * string )   // output string
{
  unsigned int i = 0;
  while (string[i]!=0) this->out(string[i++]);
}


void TextureWriter::out( const char c )                // output char
{
  buffer[this->line*this->numCols+this->column] = c;

  this->render( buffer[this->line*this->numCols+this->column],
    this->line, this->column );

  this->column++;

  if ( this->column >= this->numCols || c == '\n' ) {
    this->nl();
  }
}

void TextureWriter::nl( void )                     // newline
{
  this->render( '\0', this->line, this->column );

  this->column = 0;
  this->line++;

  if ( this->line >= this->numLines-1 ) {
    this->line = 0; // FIXME: doesn't scroll
    memset(this->buffer, 0, this->numCols*this->numLines);
    memset(this->texture, 0, this->texXSize*this->texYSize * 4 );
  }
}

void TextureWriter::back( void )                   // remove previous char
{
  if ( this->column > 2 ) {   // FIXME: can only edit line
    this->render( '\0', this->line, this->column );  // reaze cursor
    this->column--;
    this->render( '\0', this->line, this->column );  // reaze char
  }
}

void *TextureWriter::getTexture()
{
  return this->texture;
}

void TextureWriter::render( void )
{
  for (unsigned int line = 0; line < this->numLines; line++ ) {
    for (unsigned int column = 0; column < this->numCols; column++ ) {
      this->render(buffer[line*this->numCols+column], line, column );
    }
  }
}

void TextureWriter::render( int i, unsigned int line, unsigned int column )
{
  static unsigned int bit_pos_x;
  static unsigned int bit_pos_y;
  static unsigned int pixel_line_start;
  static unsigned int char_pos_y;
  static unsigned int char_pos_x;
  static unsigned char * bitmap;

  char_pos_y = line * this->fontYSize;
  char_pos_x = column * this->fontXSize;
  bitmap = SOGUIEXAMPLES_FONT[i];

  // FIXME: rendering is sloooow!
  for (bit_pos_y=0;bit_pos_y<this->fontYSize;bit_pos_y++) {
    pixel_line_start = ((bit_pos_y+char_pos_y)*this->texXSize)+char_pos_x;
    for (bit_pos_x=0;bit_pos_x<this->fontXSize;bit_pos_x++) {
      this->texture[pixel_line_start+bit_pos_x] =
        (bitmap[bit_pos_y]&(1<<(this->fontXSize-bit_pos_x)))?this->color:this->background;
    }
  }
}

void TextureWriter::cursor( )
{
  static bool blink = true;

  if ( blink ) {
    this->render( 22, this->line, this->column );
    blink = false;
  }
  else {
    this->render( 0, this->line, this->column );
    blink = true;
  }
}

float TextureWriter::getAspectRatio()
{
  return (float)this->texXSize/this->texYSize;
}
