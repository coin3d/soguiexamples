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
// File: MooExecutive.h

#ifndef MOO_EXECUTIVE_H
#define MOO_EXECUTIVE_H

#include "MooList.cpp"

class MooString;
class MooTokenizer;

class MooExecutive
{

public:

  typedef int function( int argc, char ** argv );

  struct MooCommand
  {
    MooCommand( const char * command, function * func );
    static bool find( MooCommand * item, void * data );
    const char * command;
    function * execute;
  };

  MooExecutive( void );                     // constructor
  ~MooExecutive( void );                    // destructor

  void addCommand( const char * command, function * func );
  //void addCommand( MooString & command, function * func );
  void removeCommand( const char * command );
  //void removeCommand( MooString & command );

  int execute( MooTokenizer & tokenizer );

protected:

  MooList <MooCommand *> commandList;

private:

};

#endif // !MOO_EXECUTIVE_H
