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
