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