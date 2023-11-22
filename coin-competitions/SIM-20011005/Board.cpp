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

#include "Board.h"
#include <cstdio>
#include <cassert>

SBoard *Board::sboard = new SBoard;

SBoard::SBoard()
{
  // level 1, Row 1
  solutions[0][0] = 0; solutions[0][1] = 1; solutions[0][2] = 2; solutions[0][3] = 3;
   
  // level 1, Row 2
  solutions[1][0] = 4; solutions[1][1] = 5; solutions[1][2] = 6; solutions[1][3] = 7;
   
  // level 1, Row 3   
  solutions[2][0] = 8; solutions[2][1] = 9; solutions[2][2] = 10; solutions[2][3] = 11;
   
  // level 1, Row 4
  solutions[3][0] = 12; solutions[3][1] = 13; solutions[3][2] = 14; solutions[3][3] = 15;
   
  // level 1, Col 1   
  solutions[4][0] = 0; solutions[4][1] = 4; solutions[4][2] = 8; solutions[4][3] = 12;
   
  // level 1, Col 2
  solutions[5][0] = 1; solutions[5][1] = 5; solutions[5][2] = 9; solutions[5][3] = 13;
   
  // level 1, Col 3
  solutions[6][0] = 2; solutions[6][1] = 6; solutions[6][2] = 10; solutions[6][3] = 14;
   
  // level 1, Col 4
  solutions[7][0] = 3; solutions[7][1] = 7; solutions[7][2] = 11; solutions[7][3] = 15;
   
  // level 1, Diagonal /
  solutions[8][0] = 0; solutions[8][1] = 5; solutions[8][2] = 10; solutions[8][3] = 15;
   
  // level 1, Diagonal '\' 
  solutions[9][0] = 3; solutions[9][1] = 6; solutions[9][2] = 9; solutions[9][3] = 12;
   
  // level 2, Row 1
  solutions[10][0] = 16; solutions[10][1] = 17; solutions[10][2] = 18; solutions[10][3] = 19;
   
  // level 2, Row 2
  solutions[11][0] = 20; solutions[11][1] = 21; solutions[11][2] = 22; solutions[11][3] = 23;
   
  // level 2, Row 3
  solutions[12][0] = 24; solutions[12][1] = 25; solutions[12][2] = 26; solutions[12][3] = 27;
   
  // level 2, Row 4
  solutions[13][0] = 28; solutions[13][1] = 29; solutions[13][2] = 30; solutions[13][3] = 31;
   
  // level 2, Col 1
  solutions[14][0] = 16; solutions[14][1] = 20; solutions[14][2] = 24; solutions[14][3] = 28;
   
  // level 2, Col 2
  solutions[15][0] = 17; solutions[15][1] = 21; solutions[15][2] = 25; solutions[15][3] = 29;
   
  // level 2, Col 3
  solutions[16][0] = 18; solutions[16][1] = 22; solutions[16][2] = 26; solutions[16][3] = 30;
   
  // level 2, Col 4
  solutions[17][0] = 19; solutions[17][1] = 23; solutions[17][2] = 27; solutions[17][3] = 31;
   
  // level 2, Diagonal /
  solutions[18][0] = 16; solutions[18][1] = 21; solutions[18][2] = 26; solutions[18][3] = 31;
   
  // level 2, Diagonal '\' 
  solutions[19][0] = 19; solutions[19][1] = 22; solutions[19][2] = 25; solutions[19][3] = 28;
   
  // level 3, Row 1
  solutions[20][0] = 32; solutions[20][1] = 33; solutions[20][2] = 34; solutions[20][3] = 35;
   
  // level 3, Row 2
  solutions[21][0] = 36; solutions[21][1] = 37; solutions[21][2] = 38; solutions[21][3] = 39;
   
  // level 3, Row 3
  solutions[22][0] = 40; solutions[22][1] = 41; solutions[22][2] = 42; solutions[22][3] = 43;
   
  // level 3, Row 4
  solutions[23][0] = 44; solutions[23][1] = 45; solutions[23][2] = 46; solutions[23][3] = 47;
   
  // level 3, Col 1
  solutions[24][0] = 32; solutions[24][1] = 36; solutions[24][2] = 40; solutions[24][3] = 44;
   
  // level 3, Col 2
  solutions[25][0] = 33; solutions[25][1] = 37; solutions[25][2] = 41; solutions[25][3] = 45;
   
  // level 3, Col 3
  solutions[26][0] = 34; solutions[26][1] = 38; solutions[26][2] = 42; solutions[26][3] = 46;
   
  // level 3, Col 4
  solutions[27][0] = 35; solutions[27][1] = 39; solutions[27][2] = 43; solutions[27][3] = 47;
   
  // level 3, Diagonal /
  solutions[28][0] = 32; solutions[28][1] = 37; solutions[28][2] = 42; solutions[28][3] = 47;
   
  // level 3, Diagonal '\' 
  solutions[29][0] = 35; solutions[29][1] = 38; solutions[29][2] = 41; solutions[29][3] = 44;
   
  // level 4, Row 1
  solutions[30][0] = 48; solutions[30][1] = 49; solutions[30][2] = 50; solutions[30][3] = 51;
   
  // level 4, Row 2
  solutions[31][0] = 52; solutions[31][1] = 53; solutions[31][2] = 54; solutions[31][3] = 55;
   
  // level 4, Row 3
  solutions[32][0] = 56; solutions[32][1] = 57; solutions[32][2] = 58; solutions[32][3] = 59;
   
  // level 4, Row 4
  solutions[33][0] = 60; solutions[33][1] = 61; solutions[33][2] = 62; solutions[33][3] = 63;
   
  // level 4, Col 1
  solutions[34][0] = 48; solutions[34][1] = 52; solutions[34][2] = 56; solutions[34][3] = 60;
   
  // level 4, Col 2
  solutions[35][0] = 49; solutions[35][1] = 53; solutions[35][2] = 57; solutions[35][3] = 61;
   
  // level 4, Col 3
  solutions[36][0] = 50; solutions[36][1] = 54; solutions[36][2] = 58; solutions[36][3] = 62;
   
  // level 4, Col 1
  solutions[37][0] = 51; solutions[37][1] = 55; solutions[37][2] = 59; solutions[37][3] = 63;
   
  // level 4, Diagonal /
  solutions[38][0] = 48; solutions[38][1] = 53; solutions[38][2] = 58; solutions[38][3] = 63;
   
  // level 4, Diagonal '\' 
  solutions[39][0] = 51; solutions[39][1] = 54; solutions[39][2] = 57; solutions[39][3] = 60;
   
  // Row 1 - Col 1 vertical
  solutions[40][0] = 0; solutions[40][1] = 16; solutions[40][2] = 32; solutions[40][3] = 48;
   
  // Row 1 - Col 2 vertical
  solutions[41][0] = 1; solutions[41][1] = 17; solutions[41][2] = 33; solutions[41][3] = 49;
   
  // Row 1 - Col 3 vertical
  solutions[42][0] = 2; solutions[42][1] = 18; solutions[42][2] = 34; solutions[42][3] = 50;
   
  // Row 1 - Col 4 vertical
  solutions[43][0] = 3; solutions[43][1] = 19; solutions[43][2] = 35; solutions[43][3] = 51;
   
  // Row 2 - Col 1 vertical
  solutions[44][0] = 4; solutions[44][1] = 20; solutions[44][2] = 36; solutions[44][3] = 52;
   
  // Row 2 - Col 2 vertical
  solutions[45][0] = 5; solutions[45][1] = 21; solutions[45][2] = 37; solutions[45][3] = 53;
   
  // Row 2 - Col 3 vertical
  solutions[46][0] = 6; solutions[46][1] = 22; solutions[46][2] = 38; solutions[46][3] = 54;
   
  // Row 2 - Col 4 vertical
  solutions[47][0] = 7; solutions[47][1] = 23; solutions[47][2] = 39; solutions[47][3] = 55;
   
  // Row 3 - Col 1 vertical
  solutions[48][0] = 8; solutions[48][1] = 24; solutions[48][2] = 40; solutions[48][3] = 56;
   
  // Row 3 - Col 2 vertical
  solutions[49][0] = 9; solutions[49][1] = 25; solutions[49][2] = 41; solutions[49][3] = 57;
   
  // Row 3 - Col 3 vertical
  solutions[50][0] = 10; solutions[50][1] = 26; solutions[50][2] = 42; solutions[50][3] = 58;
   
  // Row 3 - Col 4 vertical
  solutions[51][0] = 11; solutions[51][1] = 27; solutions[51][2] = 43; solutions[51][3] = 59;
   
  // Row 4 - Col 1 vertical
  solutions[52][0] = 12; solutions[52][1] = 28; solutions[52][2] = 44; solutions[52][3] = 60;
   
  // Row 4 - Col 2 vertical
  solutions[53][0] = 13; solutions[53][1] = 29; solutions[53][2] = 45; solutions[53][3] = 61;
   
  // Row 4 - Col 3 vertical
  solutions[54][0] = 14; solutions[54][1] = 30; solutions[54][2] = 46; solutions[54][3] = 62;
   
  // Row 4 - Col 4 vertical
  solutions[55][0] = 15; solutions[55][1] = 31; solutions[55][2] = 47; solutions[55][3] = 63;
   
  // 3D diag
  solutions[56][0] = 0; solutions[56][1] = 21; solutions[56][2] = 42; solutions[56][3] = 63;
   
  // xz diag
  solutions[57][0] = 0; solutions[57][1] = 17; solutions[57][2] = 34; solutions[57][3] = 51;
   
  // yz diag
  solutions[58][0] = 0; solutions[58][1] = 20; solutions[58][2] = 40; solutions[58][3] = 60;
   
  // 3D diag
  solutions[59][0] = 3; solutions[59][1] = 22; solutions[59][2] = 41; solutions[59][3] = 60;
   
  // xz diag
  solutions[60][0] = 3; solutions[60][1] = 18; solutions[60][2] = 33; solutions[60][3] = 48;
   
  // yz diag
  solutions[61][0] = 3; solutions[61][1] = 23; solutions[61][2] = 43; solutions[61][3] = 63;
   
  // 3D diag
  solutions[62][0] = 12; solutions[62][1] = 25; solutions[62][2] = 38; solutions[62][3] = 51;
   
  // xz diag
  solutions[63][0] = 12; solutions[63][1] = 29; solutions[63][2] = 46; solutions[63][3] = 63;
   
  // yz diag
  solutions[64][0] = 12; solutions[64][1] = 24; solutions[64][2] = 36; solutions[64][3] = 48;
   
  // 3D diag
  solutions[65][0] = 15; solutions[65][1] = 26; solutions[65][2] = 37; solutions[65][3] = 48;
   
  // xz diag
  solutions[66][0] = 15; solutions[66][1] = 30; solutions[66][2] = 45; solutions[66][3] = 60;
   
  // yz diag
  solutions[67][0] = 15; solutions[67][1] = 27; solutions[67][2] = 39; solutions[67][3] = 51;

  // yz diag
  solutions[68][0] = 1; solutions[68][1] = 21; solutions[68][2] = 41; solutions[68][3] = 61;
   
  // yz diag
  solutions[69][0] = 2; solutions[69][1] = 22; solutions[69][2] = 42; solutions[69][3] = 62;
   
  // yz diag
  solutions[70][0] = 13; solutions[70][1] = 25; solutions[70][2] = 37; solutions[70][3] = 49;
    
  // yz diag
  solutions[71][0] = 14; solutions[71][1] = 26; solutions[71][2] = 38; solutions[71][3] = 50;
   

  // xz diag
  solutions[72][0] = 4; solutions[72][1] = 21; solutions[72][2] = 38; solutions[72][3] = 55;
   
  // xz diag
  solutions[73][0] = 8; solutions[73][1] = 25; solutions[73][2] = 42; solutions[73][3] = 59;
   
  // xz diag
  solutions[74][0] = 7; solutions[74][1] = 22; solutions[74][2] = 37; solutions[74][3] = 52;
   
  // xz diag
  solutions[75][0] = 11; solutions[75][1] = 26; solutions[75][2] = 41; solutions[75][3] = 56;
   
  
  // Initialize solutionSpace
  int i,j,k,n;
  for (i=0;i<64;i++) {
    solutionSpace[i][0]=0;
    for (j=1;j<8;j++) {
      solutionSpace[i][j]=-1;
    }
  }

  for (i=0;i<64;i++) {
    for (j=0;j<76;j++) {
      for (k=0;k<4;k++) {
        if (solutions[j][k]==i) {
          n = solutionSpace[i][0];
          solutionSpace[i][++n]=j;
          solutionSpace[i][0]=n;
        }
      }
    }
  }
}

Board::Board()
{
  clear();
}

Board::~Board()
{
}

void
Board::clear()
{
  for (int k=0;k<4;k++)
    for (int j=0;j<4;j++)
      for (int i=0;i<4;i++)
        this->setToken(i,j,k,NONE);
}

// Returns first available slot (height) or -1
int
Board::checkPosition(int x, int y)
{
  if (x<0 || x>3 || y<0 || y>3) return -1;
  
  for (int z=0;z<4;z++) {
    if (this->getToken(x,y,z)==NONE) return z;
  }
  return -1;
}

//
// Check if col har all 4 indices covered
//
bool
Board::check(Token col, int i1, int i2, int i3, int i4)
{
  if (!(this->board[i1]&col)) return false; 
  if (!(this->board[i2]&col)) return false; 
  if (!(this->board[i3]&col)) return false; 
  if (!(this->board[i4]&col)) return false; 
  return true;
}

//
// Returns the indices making up solution sol
//
void 
Board::getSolution(int sol, int& i0, int& i1, int& i2, int& i3)
{
  if (sol>=0) {
    i0 = sboard->solutions[sol][0];
    i1 = sboard->solutions[sol][1];
    i2 = sboard->solutions[sol][2];
    i3 = sboard->solutions[sol][3];
  }
}

//
// Checks if a winning condition occurred after placing a token of
// color col at position x,y,z. Returns the solution index in solution.
//
bool
Board::validate(int x, int y, int z, Token col, int& solution)
{
  int idx = index(x,y,z);
  int num = sboard->solutionSpace[idx][0];
  for (int i=1;i<=num;i++) {
    int sol = sboard->solutionSpace[idx][i];
    if (check(col,
              sboard->solutions[sol][0],
              sboard->solutions[sol][1],
              sboard->solutions[sol][2],
              sboard->solutions[sol][3])) {
      solution=sol;
      return true;
    }
  }
  return false;
}

//
// Calculates heurestic for current board seen from col when col 
// have just placed his token at x,y,z.
//
int
Board::heurestic(Token col, int x, int y, int z)
{
  /* Scores (first is best)
     O 4-in-a-row
     O Blocked other player's 3-in-a-row
     o FIXME: 2 times 3-in-a-row w/last places available next round (winning move)
     o 3-in-a-row w/last place available next round (forces opponent)
     o 3-in-a-row w/last place !available next round (positioning)
     o Maximize 2-in-a-row's
       - Crossing 2-in-a-row where cross is available is good
     o Crossing 1-in-a-row where cross is available is good
     o Corner z=0/3 (check avail.)
     o Inner z=1/2 (check availability)
   */


  // Calculate total score of board
  int hsums[76]; // One sum for each solution
  int score=0;
  for (int i=0;i<76;i++) {
    hsums[i]=0;
    int colidx=-1;
    int availableNow=0;
    int availableLater=0;
    for (int j=0;j<4;j++) {
      int solidx = sboard->solutions[i][j];
      int val = this->board[solidx]&(RED|BLUE);
      hsums[i] += val;
      if (hsums[i]==col) colidx=j;
      if (val==NONE) {
        int solx = GET_X(solidx);
        int soly = GET_Y(solidx);
        int solz = GET_Z(solidx);
        if (checkPosition(solx,soly)==solz) availableNow++;
        else availableLater++;
      }
    }
    if (hsums[i]==col*3 &&
             (availableNow+availableLater)>=1) score+=0x00100000;
    else if (hsums[i]==col*2 &&
             (availableNow+availableLater)>=2) score+=0x0000100;
    else if (hsums[i]==col &&
             (availableNow+availableLater)>=3) {
      
      int idx = sboard->solutions[i][colidx];
      int cx = GET_X(idx);
      int cy = GET_Y(idx);
      int cz = GET_Z(idx);
      if (isCorner(cx,cy,cz)) score+=0x0000010;
      else if (isInner(cx,cy,cz)) score+=0x0000010;
      else score+=0x0000001;
    }
  }

  // Quick check for winner & forced moves
  {
    Token othercol = col==RED?BLUE:RED;
    bool forced=false;
    int idx = index(x,y,z);
    int num = sboard->solutionSpace[idx][0];
    for (int i=1;i<=num;i++) {
      int sol = sboard->solutionSpace[idx][i];
      if (hsums[sol]==col*4) return HEUR_WINNER;
      else if (hsums[sol]==othercol*3+col) forced=true;
    }
    if (forced) return HEUR_FORCED;
  }

  // Check for potential crossing solutions
  {
    for (int i=0;i<64;i++) {
      int val = this->board[i]&(RED|BLUE);
      if (val==NONE) {
        int ones=0;
        int twos=0;
        int num = sboard->solutionSpace[i][0];
        for (int j=1;j<=num;j++) {
          int sol = sboard->solutionSpace[i][j];
          if (hsums[sol]==col*2) twos++;
          else if (hsums[sol]==col*1) ones++;
        }
        if ((ones+twos)>=2) {
          score += (twos*0x10+ones)*0x100;
        }
      }
    }
  }

  return score;

  #if 0
  // Quick check for winner & forced moves
  {
    Token othercol = col==RED?BLUE:RED;
    bool forced=false;
    int idx = index(x,y,z);
    int num = sboard->solutionSpace[idx][0];
    for (int i=1;i<=num;i++) {
      int sol = sboard->solutionSpace[idx][i];
      int tmp=0;
      int availableNow=0;
      int availableLater=0;
      for (int j=0;j<4;j++) {
        int solidx = sboard->solutions[sol][j];
        int val = this->board[solidx]&(RED|BLUE);
        tmp += val;
        if (val==NONE) {
          int solx = GET_X(solidx);
          int soly = GET_Y(solidx);
          int solz = GET_Z(solidx);
          if (checkPosition(solx,soly)==solz) availableNow++;
          else availableLater++;
        }
      }
      if (tmp==col*4) return HEUR_WINNER;
      else if (tmp==othercol*3+col) forced=true;
    }
    if (forced) return HEUR_FORCED;
  }

  // Calculate total score of board
  int score=0;
  for (int i=0;i<76;i++) {
    int tmp=0;
    int colidx=-1;
    int availableNow=0;
    int availableLater=0;
    for (int j=0;j<4;j++) {
      int solidx = sboard->solutions[i][j];
      int val = this->board[solidx]&(RED|BLUE);
      tmp += val;
      if (tmp==col) colidx=j;
      if (val==NONE) {
        int solx = GET_X(solidx);
        int soly = GET_Y(solidx);
        int solz = GET_Z(solidx);
        if (checkPosition(solx,soly)==solz) availableNow++;
        else availableLater++;
      }
    }
    if (tmp==col*3 &&
             (availableNow+availableLater)>=1) score+=0x00100000;
    else if (tmp==col*2 &&
             (availableNow+availableLater)>=2) score+=0x0000100;
    else if (tmp==col &&
             (availableNow+availableLater)>=3) {
      
      int idx = sboard->solutions[i][colidx];
      int cx = GET_X(idx);
      int cy = GET_Y(idx);
      int cz = GET_Z(idx);
      if (isCorner(cx,cy,cz)) score+=0x0000010;
      else if (isInner(cx,cy,cz)) score+=0x0000010;
      else score+=0x0000001;
    }
  }

  return score;
#endif
}

//
// private methods
//

bool
Board::isCorner(int x, int y, int z)
{
  if ((x==0 || x==3) && (y==0 || y==3) && (z==0 || z==3)) return true;
  return false;
}

bool
Board::isInner(int x, int y, int z)
{
  if (x>0 && x<3 && y>0 && y<3 && z>0 && z<3) return true;
  return false;
}
