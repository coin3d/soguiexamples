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
