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