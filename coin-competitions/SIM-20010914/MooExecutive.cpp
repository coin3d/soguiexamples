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
