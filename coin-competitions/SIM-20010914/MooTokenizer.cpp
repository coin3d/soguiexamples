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
