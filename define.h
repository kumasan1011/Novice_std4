#include <stdbool.h>

//macro
typedef unsigned long long uint64;
typedef unsigned long long Hash;
typedef unsigned int  Move; 
typedef int Board;
typedef int Score;
typedef int Ply;

enum Color { Black, White, Color_NB };

enum Piece { WAL=-1, EMP=0, FU=1, KY, KE, GI, KI, KA, HI, OU, TO, NY, NE, NG, NK, UM, RY,
             SFU=1, SKY, SKE, SGI, SKI, SKA, SHI, SOU, STO, SNY, SNE, SNG, SNK, SUM, SRY,
             EFU=16,EKY, EKE, EGI, EKI, EKA, EHI, EOU, ETO, ENY, ENE, ENG, ENK, EUM, ERY,
             Piece_NB=31 };
             
struct Position {
  Board pos[256]; //実体
  Board piecePos[64]; //駒番号（使用するのは40個）とその位置
  Board pieceStock[8][32]; //使われてない（盤上にない駒）
  Board pieceCol[64]; //駒番号とその色
  Hash hashkey; 
};
