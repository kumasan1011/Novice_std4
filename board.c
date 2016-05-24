/*
//  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
//  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1,
//  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1,
//  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1,
//  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1,
//  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1,
//  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1,
//  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1,
//  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1,
//  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1,
//  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
*/


/*
  移動先
  xxxxxxxx xxxxxxxx x1111111  destination(bit0~6)

  移動元 (駒を打つ場合は駒種)
  xxxxxxxx xx111111 1xxxxxxx  starting square(bit7~13)

  成りフラグ
  xxxxxxxx x1xxxxxx xxxxxxxx  flag for promotion(bit14)

  駒打ちフラグ
  xxxxxxxx 1xxxxxxx xxxxxxxx  flag for drop(bit15) //hashに格納する際にはここまでを使う

  捕獲した駒の種類
  xxx11111 xxxxxxxx xxxxxxxx  captured piece(bit16~20)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "define.h"
#include "board.h"

void InitBoard(struct Position pos)
{
    int x,y;
    
    for( x=0; x<256; x++ )
    {
        pos.board[x] = WAL;
    }
    
    Board StartPos[10][10]={
		{ WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL },
		{ WAL,EKY,EKE,EGI,EKI,EOU,EKI,EGI,EKE,EKY },
		{ WAL,EMP,EHI,EMP,EMP,EMP,EMP,EMP,EKA,EMP },
		{ WAL,EFU,EFU,EFU,EFU,EFU,EFU,EFU,EFU,EFU },
		{ WAL,EMP,EMP,EMP,EMP,EMP,EMP,EMP,EMP,EMP },
		{ WAL,EMP,EMP,EMP,EMP,EMP,EMP,EMP,EMP,EMP },
		{ WAL,EMP,EMP,EMP,EMP,EMP,EMP,EMP,EMP,EMP },
		{ WAL,SFU,SFU,SFU,SFU,SFU,SFU,SFU,SFU,SFU },
		{ WAL,EMP,SKA,EMP,EMP,EMP,EMP,EMP,SHI,EMP },
		{ WAL,SKY,SKE,SGI,SKI,SOU,SKI,SGI,SKE,SKY },
	};
    
    for( x=1; x<=9; x++ )
    {
        for( y=1; y<=9; y++ )
        {
            Board sq = SQ( x, y );
            pos.board[sq] = StartPos[x][y];
        }
    }
    
    
}