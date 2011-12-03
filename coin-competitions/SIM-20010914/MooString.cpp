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
