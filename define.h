#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//macro

#define SQ(x,y) (((y)<<4)+(x))
#define NSQ(x) (x/16+(10-x%16)*10)


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

extern struct Position tree;

//======= Param used in fv.bin ==================================
enum {
	// pc_on_sqで使うためのテーブル
	// f_XXX : first , e_XXX : end  
	//  持ち駒の部分は、最大持ち駒数＋１（ 持ち駒無しの場合があるので ）
	f_hand_pawn   =    0, // 0
	e_hand_pawn   =   19, // = ↑+18+1
	f_hand_lance  =   38, // = ↑+18+1
	e_hand_lance  =   43, // = ↑+ 4+1
	f_hand_knight =   48, // = ↑+ 4+1
	e_hand_knight =   53, // = ↑+ 4+1
	f_hand_silver =   58, // = ↑+ 4+1
	e_hand_silver =   63, // = ↑+ 4+1
	f_hand_gold   =   68, // = ↑+ 4+1
	e_hand_gold   =   73, // = ↑+ 4+1
	f_hand_bishop =   78, // = ↑+ 4+1
	e_hand_bishop =   81, // = ↑+ 2+1
	f_hand_rook   =   84, // = ↑+ 2+1
	e_hand_rook   =   87, // = ↑+ 2+1
	fe_hand_end   =   90, // = ↑+ 2+1 , 手駒の終端
	// pc_on_sqで使うためのテーブル
	f_pawn        =   81, // = ↑ - 9 (歩は1段目には存在しないのでそれを除外してある)
	e_pawn        =  162, // = ↑+9*9 (ここ、8*9までしか使用していない)
	f_lance       =  225, // = ↑+7*9 (香も1段目には存在しないのでそれを除外してある)
	e_lance       =  306, // = ↑+9*9 (ここ、8*9までしか使用していない)
	f_knight      =  360, // = ↑+9*6 (桂は、1,2段目に存在しないのでそれを除外)
	e_knight      =  441, // = ↑+9*9 (ここも、7*9までしか使用していない)
	f_silver      =  504, // = ↑+9*6
	e_silver      =  585, // = ↑+9*9
	f_gold        =  666, // = ↑+9*9
	e_gold        =  747, // 以下、+9*9ずつ増える。
	f_bishop      =  828,
	e_bishop      =  909,
	f_horse       =  990,
	e_horse       = 1071,
	f_rook        = 1152,
	e_rook        = 1233,
	f_dragon      = 1314,
	e_dragon      = 1395,
	fe_end        = 1476, // これが最後のデータ
	kkp_hand_pawn   =   0, // 0	
	kkp_hand_lance  =  19, // +18+1 = 19
	kkp_hand_knight =  24, // + 4+1 = 24
	kkp_hand_silver =  29, // + 4+1 = ..
	kkp_hand_gold   =  34, // + 4+1
	kkp_hand_bishop =  39, // + 4+1
	kkp_hand_rook   =  42, // + 2+1
	kkp_hand_end    =  45, // + 2+1
	kkp_pawn        =  36, // kkp_hand_end - 9
	kkp_lance       = 108, // + 8*9 = 108
	kkp_knight      = 171, // + 7*9 = 171
	kkp_silver      = 252, // + 7*9 = ...
	kkp_gold        = 333, // + 9*9
	kkp_bishop      = 414, // + 9*9
	kkp_horse       = 495, // + 9*9
	kkp_rook        = 576, // + 9*9
	kkp_dragon      = 657, // + 9*9
	kkp_end         = 738  // + 9*9
};

enum { pos_n=fe_end*(fe_end+1)/2 , nsquare=81 };

extern short pc_on_sq[nsquare][pos_n];
extern short pc_on_sq2[nsquare][fe_end * (fe_end + 1)];
extern short kkp[nsquare][nsquare][kkp_end];
#define PcPcOnSq2(k,i,j)    pc_on_sq2[k][i * fe_end + j]
#define PcPcOnSq(k,i,j)     pc_on_sq[k][(i)*((i)+1)/2+(j)]
#define Inv(i) (80-i)
#define FV_SCALE 32

#define INFINITE 99999999