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