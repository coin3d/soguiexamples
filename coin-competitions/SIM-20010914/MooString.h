// File: MooString.h

#ifndef MOO_STRING_H
#define MOO_STRING_H

#include "MooList.cpp"

class MooString
{

  friend class MooOut;

public:

  MooString( void );                            // constructor
  MooString( const char * string );             // constructor
  ~MooString( void );                           // destructor

  //void append( const char * string );         // concatinate string
  //void append( MooString & string );          // concatinate to string
  void append( char c );                        // append char to string
  void remove( void );                          // remove last char
  void clear( void );                           // delete char list
  unsigned int length( void );                  // get length of current list
  void get( char * dest, unsigned int length ); // get null terminated string
  char getC( unsigned int index );              // get char at index
  bool equals( MooString & string );
  bool equals( const char * string );

protected:

  MooList <char> charList;

private:

};

#endif // !MOO_STRING_H
