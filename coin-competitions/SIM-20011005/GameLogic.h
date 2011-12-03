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

#ifndef _gamelogic_h_
#define _gamelogic_h_

#include "Board.h"

class GameLogic
{
private:
  Board board;
  int counter;
  int tokenXpos;
  int tokenYpos;
  int lastpos[3];
  Token whoseTurn;
  Token startColor;
  Token computerColor;
  bool inGame;
  int players;

  int solution;

  void nextTurn();
  bool add(int x,int y);
  bool doValidate();
public:
  GameLogic();
  ~GameLogic();

  void clear();
  bool start(Token startColor, bool onePlayer);
  bool isInGame() {return inGame;}
  bool add();
  bool validate();
  void getSolution(int& i0, int& i1, int& i2, int& i3);
  void getCurrPos(int &x, int &y);
  bool getLastPos(int &x, int &y, int &z, Token &color);
  bool undo(Token& col, int& x, int& y, int& z);
  bool move(int dx, int dy);
  bool moveTo(int x, int y);
  bool onePlayer() {return (this->players==1);}
  Token getWhoseTurn() {return this->whoseTurn;}
  bool isComputersTurn();
  void getSuggestedMove(int& x, int& y);
};

#endif // _gamelogic_h_
