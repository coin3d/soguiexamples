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
