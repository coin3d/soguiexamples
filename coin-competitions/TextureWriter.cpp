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

/*
 * Class for writing text into a bitmap buffer (to be used as a
 * texture, for instance).
 */

/* First submitted in a competition entry by Marius Bugge Monsen.
   Cleaned up and submitted as commonly available code by Marius
   Kintel. */

#include "TextureWriter.h"
#include "bitmapfont8x12.h"

#include <stdio.h>
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

void TextureWriter::render( char c, unsigned int line, unsigned int column )
{
  static unsigned int bit_pos_x;
  static unsigned int bit_pos_y;
  static unsigned int pixel_line_start;
  static unsigned int char_pos_y;
  static unsigned int char_pos_x;
  static unsigned char * bitmap;

  char_pos_y = line * this->fontYSize;
  char_pos_x = column * this->fontXSize;
  bitmap = SOGUIEXAMPLES_FONT[c];

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
