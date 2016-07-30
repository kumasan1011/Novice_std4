#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "define.h"
#include "evaluate.h"

int evaluate( struct Position *tree ){
	
	int score=0;
	int ret=0;
	int s_king_s,e_king_s,s_king_d,e_king_d;
	int sq_bk0,sq_wk0,sq_bk1,sq_wk1;
	int list0[52],list1[52];
	int nlist=0;
	int material=0;
	int i,j,k;
	
	sq_bk0 = ( tree->piecePos[1]/16-1 )*9+( tree->piecePos[1]%16-1 );
	sq_wk0 = ( tree->piecePos[2]/16-1 )*9+( tree->piecePos[2]%16-1 );
	sq_bk1 = 80 - sq_wk0;
	sq_wk1 = 80 - sq_bk0;
	
	
	//=== MATERIAL HAND=============================================
	for(i=1;i<8;i++){
		if( tree->b_hand[i] ){
			material+=PieceHandVal[i]*tree->b_hand[i];
		}
		if( tree->w_hand[i] ){
			material-=PieceHandVal[i]*tree->w_hand[i];
		}
	}
	//=== KKP HAND =================================================
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_pawn   + tree->b_hand[FU] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_lance  + tree->b_hand[KY] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_knight + tree->b_hand[KE] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_silver + tree->b_hand[GI] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_gold   + tree->b_hand[KI] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_bishop + tree->b_hand[KA] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_rook   + tree->b_hand[HI] ];

	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_pawn   + tree->w_hand[FU] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_lance  + tree->w_hand[KY] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_knight + tree->w_hand[KE] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_silver + tree->w_hand[GI] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_gold   + tree->w_hand[KI] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_bishop + tree->w_hand[KA] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_rook   + tree->w_hand[HI] ];
	//=====MAKE LIST HAND===========================================
	list0[ 0]=f_hand_pawn  + tree->b_hand[1];
	list0[ 1]=e_hand_pawn  + tree->w_hand[1];
	list0[ 2]=f_hand_lance + tree->b_hand[2];
	list0[ 3]=e_hand_lance + tree->w_hand[2];
	list0[ 4]=f_hand_knight+ tree->b_hand[3];
	list0[ 5]=e_hand_knight+ tree->w_hand[3];
	list0[ 6]=f_hand_silver+ tree->b_hand[4];
	list0[ 7]=e_hand_silver+ tree->w_hand[4];
	list0[ 8]=f_hand_gold  + tree->b_hand[5];
	list0[ 9]=e_hand_gold  + tree->w_hand[5];
	list0[10]=f_hand_bishop+ tree->b_hand[6];
	list0[11]=e_hand_bishop+ tree->w_hand[6];
	list0[12]=f_hand_rook  + tree->b_hand[7];
	list0[13]=e_hand_rook  + tree->w_hand[7];
	
	list1[ 0]=f_hand_pawn  + tree->w_hand[1];
	list1[ 1]=e_hand_pawn  + tree->b_hand[1];
	list1[ 2]=f_hand_lance + tree->w_hand[2];
	list1[ 3]=e_hand_lance + tree->b_hand[2];
	list1[ 4]=f_hand_knight+ tree->w_hand[3];
	list1[ 5]=e_hand_knight+ tree->b_hand[3];
	list1[ 6]=f_hand_silver+ tree->w_hand[4];
	list1[ 7]=e_hand_silver+ tree->b_hand[4];
	list1[ 8]=f_hand_gold  + tree->w_hand[5];
	list1[ 9]=e_hand_gold  + tree->b_hand[5];
	list1[10]=f_hand_bishop+ tree->w_hand[6];
	list1[11]=e_hand_bishop+ tree->b_hand[6];
	list1[12]=f_hand_rook  + tree->w_hand[7];
	list1[13]=e_hand_rook  + tree->b_hand[7];
	//==============================================================
	nlist=14;
	int pos,sq;
	
	for( i=1; i<=9; i++ )
    {
		for( j=1; j<=9; j++ )
        {
			
			sq=SQ(j,i);
			
			if( tree->board[sq]==EMP ) continue;
			if( tree->boardCol_b[sq])
            {
				material+=PieceVal[ tree->board[sq] ];
			}
            else
            {
                material-=PieceVal[ tree->board[sq] ];
			}
		
			pos=(i-1)*9+(j-1);
		
			switch( tree->board[sq] )
            {
				case SFU:
				ret += kkp[sq_bk0][sq_wk0][kkp_pawn + pos];
				list0[nlist] = f_pawn + pos;
				list1[nlist] = e_pawn + Inv(pos);
				nlist++;
				break;
			
				case SKY:
				ret += kkp[sq_bk0][sq_wk0][kkp_lance + pos];
				list0[nlist] = f_lance + pos;
				list1[nlist] = e_lance + Inv(pos);
				nlist++;
				break;
			
				case SKE:
				ret += kkp[sq_bk0][sq_wk0][kkp_knight + pos];
				list0[nlist] = f_knight + pos;
				list1[nlist] = e_knight + Inv(pos);
				nlist++;
				break;
			
				case SGI:
				ret += kkp[sq_bk0][sq_wk0][kkp_silver + pos];
				list0[nlist] = f_silver + pos;
				list1[nlist] = e_silver + Inv(pos);
				nlist++;
				break;
			
				case SKI: case STO: case SNY: case SNE: case SNG:
				ret += kkp[sq_bk0][sq_wk0][kkp_gold + pos];
				list0[nlist] = f_gold + pos;
				list1[nlist] = e_gold + Inv(pos);
				nlist++;
				break;
			
				case SKA:
				ret += kkp[sq_bk0][sq_wk0][kkp_bishop + pos];
				list0[nlist] = f_bishop + pos;
				list1[nlist] = e_bishop + Inv(pos);
				nlist++;
				break;
			
				case SHI:
				ret += kkp[sq_bk0][sq_wk0][kkp_rook + pos];
				list0[nlist] = f_rook + pos;
				list1[nlist] = e_rook + Inv(pos);
				nlist++;
				break;
			
				case SUM:
				ret += kkp[sq_bk0][sq_wk0][kkp_horse + pos];
				list0[nlist] = f_horse + pos;
				list1[nlist] = e_horse + Inv(pos);
				nlist++;
				break;
			
				case SRY:
				ret += kkp[sq_bk0][sq_wk0][kkp_dragon + pos];
				list0[nlist] = f_dragon + pos;
				list1[nlist] = e_dragon + Inv(pos);
				nlist++;
				break;
			
				case EFU:
				ret -= kkp[sq_bk1][sq_wk1][kkp_pawn + Inv(pos)];
				list0[nlist] = e_pawn + pos;
				list1[nlist] = f_pawn + Inv(pos);
				nlist++;
				break;
			
				case EKY:
				ret -= kkp[sq_bk1][sq_wk1][kkp_lance + Inv(pos)];
				list0[nlist] = e_lance + pos;
				list1[nlist] = f_lance + Inv(pos);
				nlist++;
				break;
			
				case EKE:
				ret -= kkp[sq_bk1][sq_wk1][kkp_knight + Inv(pos)];
				list0[nlist] = e_knight + pos;
				list1[nlist] = f_knight + Inv(pos);
				nlist++;
				break;
			
				case EGI:
				ret -= kkp[sq_bk1][sq_wk1][kkp_silver + Inv(pos)];
				list0[nlist] = e_silver + pos;
				list1[nlist] = f_silver + Inv(pos);
				nlist++;
				break;
			
				case EKI: case ETO:	case ENY: case ENE:	case ENG:
				ret -= kkp[sq_bk1][sq_wk1][kkp_gold + Inv(pos)];
				list0[nlist] = e_gold + pos;
				list1[nlist] = f_gold + Inv(pos);
				nlist++;
				break;
			
				case EKA:
				ret -= kkp[sq_bk1][sq_wk1][kkp_bishop + Inv(pos)];
				list0[nlist] = e_bishop + pos;
				list1[nlist] = f_bishop + Inv(pos);
				nlist++;
				break;
			
				case EHI:
				ret -= kkp[sq_bk1][sq_wk1][kkp_rook + Inv(pos)];
				list0[nlist] = e_rook + pos;
				list1[nlist] = f_rook + Inv(pos);
				nlist++;
				break;
			
				case EUM:
				ret -= kkp[sq_bk1][sq_wk1][kkp_horse + Inv(pos)];
				list0[nlist] = e_horse + pos;
				list1[nlist] = f_horse + Inv(pos);
				nlist++;
				break;
			
				case ERY:
				ret -= kkp[sq_bk1][sq_wk1][kkp_dragon + Inv(pos)];
				list0[nlist] = e_dragon + pos;
				list1[nlist] = f_dragon + Inv(pos);
				nlist++;
				break;
			}
		}
	}
	
	int k0,k1,l0,l1;
	int sum=0;
	for ( i=0; i<nlist; i++ )
    {
		k0 = list0[i];
		k1 = list1[i];
		for( j=0; j<=i; j++ )
        {
			l0 = list0[j];
			l1 = list1[j];
			sum += PcPcOnSq2( sq_bk0, k0, l0 );
			sum -= PcPcOnSq2( sq_bk1, k1, l1 );
		}
	}
	score+=material*FV_SCALE;
	score+=sum+ret;
	
	score/=FV_SCALE;
	/*
    score+=RankBonus[ 10-GetRank(KingPos[Black]) ];
    score-=RankBonus[ GetRank(KingPos[White]) ];
    */
	if(tree->color==White)return -score;
	else return score;
}