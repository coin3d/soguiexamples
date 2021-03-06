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
// File MooOut.cpp

#include "MooOut.h"
#include "MooString.h"
#include "font.h"

//#include <stdio.h>
#include <memory.h>

MooOut::MooOut( void )
{
  // FIXME: use memset
  /*
  for ( unsigned int line = 0; line < 25; line++ ) {
    for ( unsigned int column = 0; column < 80; column++ ) {
      buffer[line][column] = 0;
    }
  }
  */
  memset( this->buffer, 0, 25 * 80 );
  memset( this->texture, 0, 1024 * 512 * 4 );

  this->column = 0;
  this->line = 0;
  this->color = 0xff00ff00;
  this->background = 0x00000000;
}

MooOut::~MooOut( void )
{

}

void MooOut::out( MooString & string )    // output string
{
  string.charList.start( );
  do {
    this->out( string.charList.get( ) );
  } while ( string.charList.next( ) );
}

void MooOut::out( const char * string )   // output string
{
  unsigned int i = 0;
  while ( string[i] != 0 ) this->out( string[i++] );
}


void MooOut::out( const char c )                // output char
{
  //putc( c, stdout );

  buffer[this->line][this->column] = c;

  this->render( buffer[this->line][this->column],
    this->line, this->column );

  this->column++;

  if ( this->column >= 80 || c == '\n' ) {

    this->nl( );

  }

}

void MooOut::nl( void )                     // newline
{
  this->render( '\0', this->line, this->column );

  this->column = 0;
  this->line++;

  if ( this->line >= 24 ) {

    this->line = 0; // FIXME: doesn't scroll

    memset( this->buffer, 0, 25 * 80 );
    memset( this->texture, 0, 1024 * 512 * 4 );

  }

}

void MooOut::back( void )                   // remove previous char
{
  if ( this->column > 2 ) {   // FIXME: can only edit line
    this->render( '\0', this->line, this->column );  // reaze cursor
    this->column--;
    this->render( '\0', this->line, this->column );  // reaze char
  }
}

void * MooOut::pixels( void )
{
  return this->texture;
}

void MooOut::render( void )
{

  for ( unsigned int line = 0; line < 25; line++ ) {

    for ( unsigned int column = 0; column < 80; column++ ) {

      this->render( buffer[line][column], line, column );

    }

  }

}

void MooOut::render( unsigned int c, unsigned int line, unsigned int column )
{
  static unsigned int bit_pos_x;
  static unsigned int bit_pos_y;
  static unsigned int pixel_line_start;
  static unsigned int char_pos_y;
  static unsigned int char_pos_x;
  static unsigned char * bitmap;

  char_pos_y = line * 12;
  char_pos_x = column * 8;
  bitmap = font[c];

  // FIXME: rendering is sloooow!

  for ( bit_pos_y = 0; bit_pos_y < 12; bit_pos_y++ ) {

    pixel_line_start = ( ( bit_pos_y + char_pos_y ) * 1024 ) + char_pos_x;
			
    for ( bit_pos_x = 0; bit_pos_x < 8; bit_pos_x++ ) {

      this->texture[ pixel_line_start + bit_pos_x ] =
        ( bitmap[bit_pos_y] & ( 1 << ( 8 - bit_pos_x ) ) ) ? this->color : this->background;

    }

  }

}

void MooOut::cursor( )
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
