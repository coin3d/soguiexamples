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
// File MooString.cpp

#include "MooString.h"

MooString::MooString( void )
{

}

MooString::MooString( const char * string )             // constructor
{
  unsigned int i = 0;
  while( string[i] != 0 )
    this->charList.append( string[i++] );
}

MooString::~MooString( void )                           // destructor
{
  this->clear( );
}

void MooString::append( char c )                        // user has input a char
{
  this->charList.append( c );
}

void MooString::remove( )                               // user has deleted a char ( backspace )
{
  this->charList.end( );
  this->charList.remove( );
}

void MooString::clear( void )                           // delete char list
{
  this->charList.empty( );
}

unsigned int MooString::length( void )                  // get length of current list
{
  return ( this->charList.length( ) );
}

void MooString::get( char * dest, unsigned int length ) // create null terminated string
{
  unsigned int i = 0;

  this->charList.start( );

  do {
    dest[i] = this->charList.get( );
  } while ( ( length > ++i ) && this->charList.next( ) );

  dest[i] = 0;

}

char MooString::getC( unsigned int index )              // get char at index
{
  if ( this->charList.length( ) < index )
    return 0;

  return this->charList.get( index );
}

bool MooString::equals( MooString & string )
{
  unsigned int i = 0;
  bool a = true;
  bool b = true;
  char c = 0;
  char d = 0;

  this->charList.start( );
  string.charList.start( );

  do {
    c = this->charList.get( );
    d = string.charList.get( );
    
    if ( c != d ) return false;
    
    a = this->charList.next( );
    b = string.charList.next( );

  } while ( a && b );

  if ( a != b ) return false;

  return true;

}

bool MooString::equals( const char * string )
{
  unsigned int i = 0;
  char c = 0;

  this->charList.start( );

  do {
    c = this->charList.get( );
    if ( string[i++] != c )
      return false;
  } while ( this->charList.next( ) );

  if ( string[i] != 0 )
    return false;

  return true;

}
