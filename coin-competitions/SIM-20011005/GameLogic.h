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
