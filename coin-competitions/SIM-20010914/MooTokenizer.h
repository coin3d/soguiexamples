/**************************************************************************\
 *
 *  This file is part of a set of example programs for the Coin library.
 *  Copyright (C) 2000-2003 by Systems in Motion. All rights reserved.
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
// File: MooTokenizer.h

#ifndef MOO_TOKENIZER_H
#define MOO_TOKENIZER_H

#include "MooList.cpp"

class MooString;

class MooTokenizer
{

public:

  MooTokenizer( void );                                 // constructor
  ~MooTokenizer( void );                                // destructor

  void tokenize( MooString & string );                       // create tokens from string
  void clear( void );                                        // delete token list

  unsigned int length( void );                          // get number of tokens
  void get( MooString ** dest, unsigned int length );   // get tokens
  MooString * gets( unsigned int index );               // get token at index

protected:

  MooList <MooString *> tokenList;                      // the command tokens

private:

};

#endif // !MOO_STRING_H
