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
  memset( this->texture, 0, 640 * 300 * 4 );

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


void MooOut::out( char c )                // output char
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
    memset( this->texture, 0, 640 * 300 * 4 );

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

void MooOut::render( char c, unsigned int line, unsigned int column )
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

    pixel_line_start = ( ( bit_pos_y + char_pos_y ) * 640 ) + char_pos_x;
			    
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