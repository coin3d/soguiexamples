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
// File: MooOut.h

// Interface class

#ifndef MOO_OUT_H
#define MOO_OUT_H

class MooString;

class MooOut
{

public:

  MooOut( void );                     // constructor
  ~MooOut( void );                    // destructor
  void out( MooString & string );     // output string
  void out( const char * string );    // output string
  void out( const char c );           // output char
  void nl( void );                    // newline
  void back( void );                  // remove previous char
  void * pixels( void );              // get pixelbuffer
  void render( void );                // render charbuffer to pixelbuffer
  void render( char c,                // render character to pixelbuffer
    unsigned int line,
    unsigned int column );
  void cursor( );                     // update cursor

protected:

private:
  
  char buffer[25][80];
  unsigned int texture[640 * 300];
  unsigned int color;
  unsigned int background;
  unsigned int column;
  unsigned int line;

};

#endif // !MOO_OUT_H