#ifndef _board_h_
#define _board_h_

#define HEUR_WINNER  0x10000000
#define HEUR_FORCED  0x08000000

#define GET_X(idx) (idx&0x03);
#define GET_Y(idx) (idx&0x0c)>>2;
#define GET_Z(idx) (idx&0x30)>>4;

enum Token {NONE=0,RED=0x0100,BLUE=0x1000,MASK=0xff};

class SBoard
{
public:
  int solutionSpace[64][8]; // Which solution touches what position, 
                            // first index is number of solutions.
  int solutions[76][4];     // The solution indices to board.
public:
  SBoard();

  friend class Board;
};

class Board
{
  int board[4*4*4]; //Contains NONE or RED||BLUE + move #.

  int index(int x, int y, int z) {return x+4*y+16*z;}
  bool isCorner(int x, int y, int z);
  bool isInner(int x,int y,int z);
public:
  static SBoard *sboard;
  Board();
  ~Board();

  int getToken(int x, int y, int z) {return this->board[x+y*4+z*16];}
  void setToken(int x, int y, int z, int val) {this->board[x+y*4+z*16]=val;}
  bool check(Token col, int i1, int i2, int i3, int i4);
  void clear();
  int checkPosition(int x,int y);
  bool validate(int x, int y,int z, Token col, int& solution);
  void getSolution(int sol, int& i0, int& i1, int& i2, int& i3);
  int heurestic(Token col, int x, int y, int z);
};

#endif // _board_h_
