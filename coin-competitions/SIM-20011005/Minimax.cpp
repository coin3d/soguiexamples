/**************************************************************************\
 *
 *  This file is part of a set of demo programs for the Coin library.
 *  Copyright (C) 2000-2001 by Systems in Motion. All rights reserved.
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
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
\**************************************************************************/

#include "Minimax.h"
#include "GameLogic.h"
#include <string.h>
#include <limits.h>
#include <stdio.h>

Queue Minimax::q;
SbTime Minimax::expire;

Minimax::Minimax(Minimax *parent)
  :board(parent->board)
{
  this->parent=parent;
  this->depth=0;
  this->score=0;
  this->minimaxscore=0;
  this->selectedChild=-1;
  for (int i=0;i<16;i++) this->children[i]=NULL;
}

Minimax::Minimax(Board& rootboard)
  :board(rootboard)
{
  this->parent = NULL;
  this->depth=0;
  this->score=0;
  this->minimaxscore=0;
  this->selectedChild=-1;
  for (int i=0;i<16;i++) this->children[i]=NULL;
}

//
// col is whose turn.
//
void
Minimax::buildTree(Token col)
{
  int i,j,k;
  Minimax *forcedMove=NULL;
  // Iterate through all valid moves.
  for (j=0;j<4;j++) {
    for (i=0;i<4;i++) {
      k = this->board.checkPosition(i,j);
      if (k!=-1) { //Valid move
        Minimax *newnode = new Minimax(this);
        newnode->board.setToken(i,j,k,col);
        int s = newnode->evaluate(col,i,j,k);
        newnode->depth = this->depth+1;
        this->children[j*4+i]=newnode;
        if (abs(s)>=HEUR_FORCED) {  //Pre-empt winner/blocker
          forcedMove = newnode;
          break;
        }
      }
    }
    if (forcedMove) break;
  }

  // Make sure forced moved are followed
  // We may want to adjust this when the forced move is difficult to 
  // see for a human player.
  if (forcedMove) {
    for (i=0;i<16;i++) {
      Minimax *node = this->children[i];
      if (node && node!=forcedMove) {
        delete node;
        this->children[i]=NULL;
      }
    }
    // Always enqueue forcing moves, but not winning ones.
    if (abs(forcedMove->score)<HEUR_WINNER) {
      Minimax::q.enqueue(forcedMove);
    }
  }
  else {
    // Enqueue for breadth first traversal
    for (i=0;i<16;i++) {
      Minimax *node = this->children[i];
      if (node) Minimax::q.enqueue(node);
    }
  }

  // Dequeue for breadth first traversal
  Token nextcol = col;
  Minimax *next;
  while ((!Minimax::expired()) && (next = Minimax::q.dequeue())) {
    if (next->depth>this->depth) 
      nextcol = col==RED?BLUE:RED;
    next->buildTree(nextcol);
  }
  if (Minimax::expired()) {
    Minimax::q.clear();
  }
}

//
// Evaluated current board
//
int
Minimax::evaluate(Token col, int x, int y, int z)
{
  int s=this->board.heurestic(col,x,y,z);
  if (this->depth%2==0) this->score=-s; //Negamax
  else this->score=s;
  return this->score;
}

Minimax *
Minimax::getNextSibling()
{
  if (!this->parent) return NULL;
  for (int nextidx=this->childIdx+1;nextidx<16;nextidx++) {
    if (this->parent->children[nextidx]!=NULL) 
      return this->parent->children[nextidx];
  }
  return NULL;
}

Minimax *
Minimax::getFirstChild()
{
  for (int i=0;i<16;i++) {
    if (this->children[i]!=NULL) 
      return this->children[i];
  }
  return NULL;
}

//
// Traverses tree using Minimax (modified to 'negamax') algorithm
//
int
Minimax::doMinimax()
{
  int minimaxVal, idx, val;
  bool leaf=true;
//    bool max = (this->depth%2==0);
  minimaxVal=-INT_MAX;
//    if (max) minimaxVal=-MAXINT;
//    else minimaxVal=MAXINT;

  for (int i=0;i<16;i++) {
    Minimax *c = this->children[i];
    if (c) {
      leaf=false;
      val = c->doMinimax();
      if (val>minimaxVal) {
        minimaxVal=val;
        idx=i;
      }
//        if (max && val>minimaxVal) {
//          minimaxVal=val;
//          idx=i;
//        }
//        else if (!max && val<minimaxVal) {
//          minimaxVal=val;
//          idx=i;
//        }
    }
  }
  if (!leaf) {
    this->selectedChild=idx;
    this->minimaxscore=minimaxVal;
    return this->minimaxscore;
  }
  return this->score;
}

void
Minimax::getMove(int& x, int& y)
{
  x = this->selectedChild&0x03;
  y = (this->selectedChild&0x0c)>>2;
}

//
// col = whose turn
// Returns suggested x&y pos
//
void
Minimax::calcMove(Token col, int& x, int& y)
{
  Minimax::q.clear();
  Minimax::expire = SbTime::getTimeOfDay()+SbTime(2,0);
  
  buildTree(col);
  Minimax::q.clear();
  doMinimax();
  getMove(x,y);
}

void
Minimax::traceMove()
{
  int x,y;
  if (this->selectedChild>=0) {
    x = this->selectedChild&0x03;
    y = (this->selectedChild&0x0c)>>2;
//      printf("Score: %08x / %08x move: %d,%d (d=%d)\n",
//             abs(this->score),abs(this->minimaxscore),x,y,this->depth);
    this->children[this->selectedChild]->traceMove();
  }
//    else
//      printf("Score: %08x\n",abs(this->score));
}

bool
Minimax::expired()
{
  return (SbTime::getTimeOfDay()>Minimax::expire);
}
