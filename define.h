#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//macro

#define SQ(x,y) (((y)<<4)+(x))
#define NSQ(x) (x/16+(10-x%16)*10)

#define KingPos(color) ( color? (pos->piecePos[2]):(pos->piecePos[1]) )

/*
  移動先
  xxxxxxxx xxxxxxxx 11111111  destination(bit0~7)
  移動元 (駒を打つ場合は駒種)
  xxxxxxxx 11111111 xxxxxxxx  starting square(bit8~15)
  成りフラグ
  xxxxxxx1 xxxxxxxx xxxxxxxx  flag for promotion(bit16)
  駒打ちフラグ
  xxxxxx1x xxxxxxxx xxxxxxxx  flag for drop(bit17)
  捕獲した駒の種類
  x11111xx xxxxxxxx xxxxxxxx  captured piece(bit18~22)
  
  //Todo : Hashに格納するときのことを考える
*/


#define AddTo(move)  (move)
#define AddFrom(move) ((move)<<0x08)
#define AddPro(move)   ((move)<<0x10)
#define AddDrop(move)  ((move)<<0x11)
#define AddCap(move)   ((move)<<0x12)

#define Is2FU(color,File) (color? (((Is2FU_w)>>File) & 0x01):(((Is2FU_b)>>File) & 0x01))
#define Add2FU(File) (1<<(10-File))

#define GetTo(move)  (((move)>>0x00)& 0xff)
#define GetFrom(move) (((move)>>0x08)& 0xff) 
#define GetPro(move)   (((move)>>0x10)& 0x01)
#define GetDrop(move)  (((move)>>0x11)& 0x01)
#define GetCap(move)   (((move)>>0x12)& 0x1f)

typedef unsigned long long uint64;
typedef unsigned long long Hash;
typedef unsigned int  Move; 
typedef int Board;
typedef int Piece;
typedef int Color;

enum Color { Black, White, Color_NB };

enum Piece { WAL=-1, EMP=0, FU=1, KY, KE, GI, KI, KA, HI, OU, TO, NY, NE, NG, NK, UM, RY,
             SFU=1, SKY, SKE, SGI, SKI, SKA, SHI, SOU, STO, SNY, SNE, SNG, SNK, SUM, SRY,
             EFU=16,EKY, EKE, EGI, EKI, EKA, EHI, EOU, ETO, ENY, ENE, ENG, ENK, EUM, ERY,
             Piece_NB=31 };
             
struct Position {
  Board board[256]; //実体
  Board b_hand[8]; //先手持ち駒
  Board w_hand[8]; //後手持ち駒
  Board boardNum[256];
  Board piecePos[64]; //駒番号（使用するのは40個）とその位置
  Board pieceStock[8][32]; //使われてない（盤上にない駒）
  //Board pieceCol_b[64]; //駒番号とその色
  //Board pieceCol_w[64]; //駒番号とその色
  Board boardCol_b[256];
  Board boardCol_w[256];
  Board Is2FU_b;
  Board Is2FU_w;
  Color color;
  Hash hashkey; 
};