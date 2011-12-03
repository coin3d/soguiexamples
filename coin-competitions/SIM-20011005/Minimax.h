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

#ifndef _minimax_h_
#define _minimax_h_

#include "Board.h"
#include <stdlib.h>
#include <Inventor/SbTime.h>

class Minimax;
class Queue
{
  struct QNode {
    Minimax *node;
    struct QNode *next;
  };
  QNode *first;
  QNode *last;
public:
  Queue() {first=last=NULL;}
  void enqueue(Minimax *node) {
    QNode *newnode = new QNode;
    newnode->node=node;
    newnode->next=NULL;
    if (!first) first=newnode;
    else last->next=newnode;
    last=newnode;
  }
  Minimax *dequeue() {
    if (!first) return NULL;
    Minimax *node = first->node;
    QNode *ftmp = first;
    first=first->next;
    if (!first) last=NULL;
    delete ftmp;
    return node;
  }
  void clear() {
    QNode *node = first;
    QNode *tmp;
    while (node) {
      tmp=node->next;
      delete node;
      node=tmp;
    }
    first=last=NULL;
  }
};

class Minimax
{
  static Queue q;
  static SbTime expire; // Search expiration time
  Board board;
  int score;
  int minimaxscore;
  Minimax *parent;
  Minimax *children[16];
  bool isTraversed;
  int childIdx; //Which index am I in my parent's children[]
  int selectedChild; //Which child did I get my score from?
  int depth;

  static bool expired();
public:
  Minimax(Minimax *parent);
  Minimax(Board& rootboard);
  void run();
  void buildTree(Token col);
  int evaluate(Token col, int x, int y, int z);
  int doMinimax();
  void getMove(int& x, int& y);
  void calcMove(Token col, int& x, int& y);
  Minimax *getNextSibling();
  Minimax *getFirstChild();
  void traceMove();
};

#endif
