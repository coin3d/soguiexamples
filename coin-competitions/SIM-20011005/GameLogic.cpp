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

#include "GameLogic.h"
#include "Minimax.h"
#include <stdio.h>
#include <assert.h>

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void
GameLogic::clear()
{
  this->board.clear();
  this->counter=0;
  this->whoseTurn=NONE;
  this->inGame=false;
  this->tokenXpos=-1;
  this->tokenYpos=-1;
  this->solution=-1;
}

bool
GameLogic::start(Token startColor, bool onePlayer)
{
  clear();
  this->lastpos[0]=-1;
  this->lastpos[1]=-1;
  this->lastpos[2]=-1;
  this->whoseTurn = startColor;
  this->startColor=startColor;
  this->inGame=true;
  this->tokenXpos=0;
  this->tokenYpos=0;
  if (onePlayer) {
    this->players=1;
    if (this->startColor==RED) this->computerColor=BLUE;
    else this->computerColor=RED;
  }
  else {
    this->players=2;
    this->computerColor=NONE;
  }
  return true;
}

bool
GameLogic::add()
{
  if (!this->inGame) return false;
  int x,y;
  getCurrPos(x,y);
  return add(x,y);
}

bool 
GameLogic::isComputersTurn()
{
  return (onePlayer() && getWhoseTurn()==this->computerColor);
}

bool
GameLogic::validate()
{
  bool winner=doValidate();
  if (winner) this->inGame=false;
  return winner;
}

void
GameLogic::getSolution(int& i0,int& i1,int& i2,int& i3)
{
  this->board.getSolution(this->solution,i0,i1,i2,i3);
}

void 
GameLogic::getCurrPos(int &x, int &y)
{
  x = this->tokenXpos;
  y = this->tokenYpos;
}

//
// Gets last position and color (RED || BLUE)
//
bool 
GameLogic::getLastPos(int &x, int &y, int &z, Token &color)
{
  x = this->lastpos[0];
  if (x==-1) return false;
  y = this->lastpos[1];
  z = this->lastpos[2];
  color = (Token)(this->board.getToken(x,y,z)&(RED|BLUE));
  
  return true;
}

//
// Undo last move. Returns undid color and position.
//
bool
GameLogic::undo(Token& col, int& x, int& y, int& z)
{
  if (!this->isInGame()) return false;
  if (this->getLastPos(x,y,z,col)) {
    this->board.setToken(x,y,z,NONE);

    this->counter--;
    this->nextTurn();

    //update lastpos

    //Search for last placed token
    int i,j,k,val;
    for (k=0;k<4;k++) {
      for (j=0;j<4;j++) {
        for (i=0;i<4;i++) {
          val = this->board.getToken(i,j,k);
          if ((val&MASK)==this->counter-1) break;
        }
        if (i<4) break;
      }
      if (j<4) break;
    }
    if (k<4) {
      this->lastpos[0]=i;
      this->lastpos[1]=j;
      this->lastpos[2]=k;
    }
    else { // Undid First move
      this->lastpos[0]=-1;
      this->lastpos[1]=-1;
      this->lastpos[2]=-1;
    }
    return true;
  }
  return false;
}

bool
GameLogic::move(int dx, int dy)
{
  return this->moveTo(this->tokenXpos+dx,this->tokenYpos+dy);
}

bool
GameLogic::moveTo(int x, int y)
{
  if (!this->inGame) return false;
  if (x>=0 && x<4) this->tokenXpos=x;
  if (y>=0 && y<4) this->tokenYpos=y;
  return true;
}

void
GameLogic::getSuggestedMove(int& x, int& y)
{
  Token col = getWhoseTurn();

  Minimax root(this->board);
  root.calcMove(col,x,y);
//    root.traceMove();
}

//
// Private methods
//

void 
GameLogic::nextTurn() 
{
  if (this->whoseTurn==RED) this->whoseTurn=BLUE;
  else this->whoseTurn=RED;
}

bool
GameLogic::add(int x, int y)
{
  int z=this->board.checkPosition(x,y);
  
  if (z!=-1) {
    this->board.setToken(x,y,z,this->whoseTurn | this->counter++);
    this->lastpos[0]=x;
    this->lastpos[1]=y;
    this->lastpos[2]=z;
    nextTurn();
    return true;
  }
  else return false;
}

bool
GameLogic::doValidate()
{
  int x,y,z;
  Token col;
  int solution;
  
  if (this->getLastPos(x,y,z,col)) {
    bool ok = this->board.validate(x,y,z,col,solution);
    if (ok) this->solution=solution;
    return ok;
  }
  return false;
}
