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
