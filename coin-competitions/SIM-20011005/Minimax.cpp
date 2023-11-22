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

#include "Minimax.h"
#include "GameLogic.h"
#include <cstring>
#include <climits>
#include <cassert>
#include <cstdio>

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
        if (abs(s)>=HEUR_FORCED) {  //Preempt winner/blocker
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
  // FIXME: just to check to see if we're using idx uninitialized
  // further down. 20020107 mortene.
  int idx = INT_MAX;

  int minimaxVal, val;
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
    // FIXME: just to check to see if we're using idx uninitialized.
    // (We're getting a compiler warning here from g++ 2.95.3, at
    // least, and I'm too lazy right now to try to grok the code above
    // to see if g++'s concern is actually valid. Just asserting is
    // simpler. ;-)) 20020107 mortene.
    assert(idx != INT_MAX);
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
