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
// File MooExecutive.cpp

#include "MooExecutive.h"
#include "MooString.h"
#include "MooTokenizer.h"

MooExecutive::MooCommand::MooCommand( const char * command, function * execute )
{
  this->command = command;
  this->execute = execute;
}

bool MooExecutive::MooCommand::find( MooCommand * item, void * data )
{
  unsigned int i = 0;
  char * string = ( char * ) data;

  while ( ( item->command[i] == string[i] ) &&
          ( item->command[i] != 0 ) &&
          ( string[i] != 0 ) ) i++;

  if ( item->command[i] == string[i] ) return true;

  return false;

}

MooExecutive::MooExecutive( void )
{

}

MooExecutive::~MooExecutive( void )
{
  if ( ! this->commandList.start( ) )
    return;

  do {
    delete this->commandList.get( );
  } while ( this->commandList.next( ) );

  this->commandList.empty( );
}

void MooExecutive::addCommand( const char * command, function * execute )
{
  MooCommand * com = new MooCommand( command, execute );
  this->commandList.append( com );
}

void MooExecutive::removeCommand( const char * command )
{
  this->commandList.search( MooCommand::find, ( void * ) command );
  this->commandList.remove( );
}

int MooExecutive::execute( MooTokenizer & tokenizer )
{
  // Find command
  MooString * string = tokenizer.gets( 0 );
  if ( ! string ) return -1;
  unsigned int length = string->length( );
  char * chars = new char[length + 1];
  string->get( chars, length + 1 );
  if ( ! this->commandList.search( MooCommand::find, ( void * ) chars ) ) {
    delete chars;
    return -1;
  }
  delete chars;
  MooCommand * command = this->commandList.get( );

  // Build argument list
  unsigned int i, argc = tokenizer.length( );
  char ** argv = new char * [argc];
  MooString ** strv = new MooString * [argc];
  tokenizer.get( strv, argc );
  for ( i = 0; i < argc; i++ ) {
    length = strv[i]->length( );
    argv[i] = new char [length + 1];
    strv[i]->get( argv[i], length );
  }

  // Execute command
  command->execute( argc, argv );

  for ( i = 0; i < argc; i++ ) {
    delete argv[i];
  }
  delete argv;
  delete strv;

  return 0;
}
