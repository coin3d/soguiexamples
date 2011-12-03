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
// File MooTokenizer.cpp

#include "MooTokenizer.h"
#include "MooString.h"

MooTokenizer::MooTokenizer( void )                  // constructor
{

}

MooTokenizer::~MooTokenizer( void )                               // destructor
{
  this->clear( );
}

void MooTokenizer::tokenize( MooString & string )                  // create tokens from string
{
  unsigned int index = 0;
  unsigned int length = string.length( );
  MooString * token = 0L;
  char c = 0;

  do {

    while( ( string.getC( index ) == ' ' ) && ( index < length ) )
      index++;

    if ( index >= length ) break;

    token = new MooString( );

    while( ( index < length ) ) {
      c = string.getC( index++ );
      if ( c == ' ' ) break;
      token->append( c );
    }

    if ( token )
      this->tokenList.append( token );
    token = 0L;

  } while ( index < length );

}

void MooTokenizer::clear( void )                                   // delete token list
{
  if ( ! this->tokenList.start( ) )
    return;

  do {
    delete this->tokenList.get( );
  } while ( this->tokenList.next( ) );

  this->tokenList.empty( );

}

unsigned int MooTokenizer::length( void )                         // get number of tokens
{
  return this->tokenList.length( );
}

void MooTokenizer::get( MooString ** dest, unsigned int length )  // get tokens
{

  unsigned int i = 0;

  this->tokenList.start( );

  do {
    dest[i] = this->tokenList.get( );
  } while ( this->tokenList.next( ) && ( length > ++i ) );

}

MooString * MooTokenizer::gets( unsigned int index )              // get token at index
{
  if ( this->tokenList.length( ) > index )
    return this->tokenList.get( index );
  return 0L;
}
