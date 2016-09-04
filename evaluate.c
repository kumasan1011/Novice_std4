#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "define.h"
#include "evaluate.h"

/*
Score evaluate( struct Position *ptree ){
	
	int score=0;
	int ret=0;
	int s_king_s,e_king_s,s_king_d,e_king_d;
	int sq_bk0,sq_wk0,sq_bk1,sq_wk1;
	int list0[52],list1[52];
	int nlist=0;
	int material=0;
	int i,j,k;
	
	sq_bk0 = ( ptree->piecePos[1]/16-1 )*9+( ptree->piecePos[1]%16-1 );
	sq_wk0 = ( ptree->piecePos[2]/16-1 )*9+( ptree->piecePos[2]%16-1 );
	sq_bk1 = 80 - sq_wk0;
	sq_wk1 = 80 - sq_bk0;
	
	
	//=== MATERIAL HAND=============================================
	for(i=1;i<8;i++){
		if( ptree->b_hand[i] ){
			material+=PieceHandVal[i]*ptree->b_hand[i];
		}
		if( ptree->w_hand[i] ){
			material-=PieceHandVal[i]*ptree->w_hand[i];
		}
	}
	//=== KKP HAND =================================================
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_pawn   + ptree->b_hand[FU] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_lance  + ptree->b_hand[KY] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_knight + ptree->b_hand[KE] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_silver + ptree->b_hand[GI] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_gold   + ptree->b_hand[KI] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_bishop + ptree->b_hand[KA] ];
	ret += kkp[sq_bk0][sq_wk0][ kkp_hand_rook   + ptree->b_hand[HI] ];

	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_pawn   + ptree->w_hand[FU] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_lance  + ptree->w_hand[KY] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_knight + ptree->w_hand[KE] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_silver + ptree->w_hand[GI] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_gold   + ptree->w_hand[KI] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_bishop + ptree->w_hand[KA] ];
	ret -= kkp[sq_bk1][sq_wk1][ kkp_hand_rook   + ptree->w_hand[HI] ];
	//=====MAKE LIST HAND===========================================
	list0[ 0]=f_hand_pawn  + ptree->b_hand[1];
	list0[ 1]=e_hand_pawn  + ptree->w_hand[1];
	list0[ 2]=f_hand_lance + ptree->b_hand[2];
	list0[ 3]=e_hand_lance + ptree->w_hand[2];
	list0[ 4]=f_hand_knight+ ptree->b_hand[3];
	list0[ 5]=e_hand_knight+ ptree->w_hand[3];
	list0[ 6]=f_hand_silver+ ptree->b_hand[4];
	list0[ 7]=e_hand_silver+ ptree->w_hand[4];
	list0[ 8]=f_hand_gold  + ptree->b_hand[5];
	list0[ 9]=e_hand_gold  + ptree->w_hand[5];
	list0[10]=f_hand_bishop+ ptree->b_hand[6];
	list0[11]=e_hand_bishop+ ptree->w_hand[6];
	list0[12]=f_hand_rook  + ptree->b_hand[7];
	list0[13]=e_hand_rook  + ptree->w_hand[7];
	
	list1[ 0]=f_hand_pawn  + ptree->w_hand[1];
	list1[ 1]=e_hand_pawn  + ptree->b_hand[1];
	list1[ 2]=f_hand_lance + ptree->w_hand[2];
	list1[ 3]=e_hand_lance + ptree->b_hand[2];
	list1[ 4]=f_hand_knight+ ptree->w_hand[3];
	list1[ 5]=e_hand_knight+ ptree->b_hand[3];
	list1[ 6]=f_hand_silver+ ptree->w_hand[4];
	list1[ 7]=e_hand_silver+ ptree->b_hand[4];
	list1[ 8]=f_hand_gold  + ptree->w_hand[5];
	list1[ 9]=e_hand_gold  + ptree->b_hand[5];
	list1[10]=f_hand_bishop+ ptree->w_hand[6];
	list1[11]=e_hand_bishop+ ptree->b_hand[6];
	list1[12]=f_hand_rook  + ptree->w_hand[7];
	list1[13]=e_hand_rook  + ptree->b_hand[7];
	//==============================================================
	nlist=14;
	int pos,sq;
	
	for( i=1; i<=9; i++ )
    {
		for( j=1; j<=9; j++ )
        {
			
			sq=SQ(j,i);
			
			if( ptree->board[sq]==EMP ) continue;
			if( ptree->boardCol_b[sq])
            {
				material+=PieceVal[ ptree->board[sq] ];
			}
            else
            {
                material-=PieceVal[ ptree->board[sq] - 15 ];
			}
		
			pos=(i-1)*9+(j-1);
		
			switch( ptree->board[sq] )
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
	
    //score+=RankBonus[ 10-GetRank(KingPos[Black]) ];
    //score-=RankBonus[ GetRank(KingPos[White]) ];
    
	if(ptree->color==White)return -score;
	else return score;
}
*/

#define I2HandPawn(hand)    ( hand == Black ? ptree->b_hand[FU] : ptree->w_hand[FU] )
#define I2HandLance(hand)   ( hand == Black ? ptree->b_hand[KY] : ptree->w_hand[KY] )
#define I2HandKnight(hand)  ( hand == Black ? ptree->b_hand[KE] : ptree->w_hand[KE] )
#define I2HandSilver(hand)  ( hand == Black ? ptree->b_hand[GI] : ptree->w_hand[GI] )
#define I2HandGold(hand)    ( hand == Black ? ptree->b_hand[KI] : ptree->w_hand[KI] )
#define I2HandBishop(hand)  ( hand == Black ? ptree->b_hand[KA] : ptree->w_hand[KA] )
#define I2HandRook(hand)    ( hand == Black ? ptree->b_hand[HI] : ptree->w_hand[HI] )

// なんでこれ ptree にしたんだっけ？
Score evaluate( struct Position* ptree )
{
	Score scoreBoard;
	Score scoreTurn ;
	Score sum[3][2];
	Score material=0;
	Board sq_bk,sq_wk;
	BonaPiece pieceListFb[38],pieceListFw[38];
	int nlist=0;
	int num;
	int i,j,k;
	
	sq_bk = z2sq[ptree->piecePos[1]];
	sq_wk = z2sq[ptree->piecePos[2]];

	for(i=1;i<8;i++){
		if( ptree->b_hand[i] ){
			material+=PieceHandVal[i]*ptree->b_hand[i];
		}
		if( ptree->w_hand[i] ){
			material-=PieceHandVal[i]*ptree->w_hand[i];
		}
	}

#define FOO(hand, Piece, list0_index, list1_index)    \
	for ( i = I2Hand##Piece(hand); i >= 1; --i) {     \
		pieceListFb[nlist] = list0_index + i;         \
		pieceListFw[nlist] = list1_index + i;         \
		++nlist; \
	}

	FOO( Black, Pawn  , f_hand_pawn  , e_hand_pawn  )
	FOO( White, Pawn  , e_hand_pawn  , f_hand_pawn  )
	FOO( Black, Lance , f_hand_lance , e_hand_lance )
	FOO( White, Lance , e_hand_lance , f_hand_lance )
	FOO( Black, Knight, f_hand_knight, e_hand_knight)
	FOO( White, Knight, e_hand_knight, f_hand_knight)
	FOO( Black, Silver, f_hand_silver, e_hand_silver)
	FOO( White, Silver, e_hand_silver, f_hand_silver)
	FOO( Black, Gold  , f_hand_gold  , e_hand_gold  )
	FOO( White, Gold  , e_hand_gold  , f_hand_gold  )
	FOO( Black, Bishop, f_hand_bishop, e_hand_bishop)
	FOO( White, Bishop, e_hand_bishop, f_hand_bishop)
	FOO( Black, Rook  , f_hand_rook  , e_hand_rook  )
	FOO( White, Rook  , e_hand_rook  , f_hand_rook  )
#undef FOO
	
	Board sq;

	for( i=1; i<=40; i++ )
	{
		if( ptree->piecePos[i] == EMP ) continue;

		if( ptree->boardCol_b[ptree->piecePos[i]] )
		{
			material += PieceVal[ ptree->board[ptree->piecePos[i]] ]; 
		}
		else {
			material -= PieceVal[ ptree->board[ptree->piecePos[i]] - 15 ];
		}
	}	
	
	for( i=3; i<=40; i++ )
	{
		const int z = ptree->piecePos[i];
		if( z == EMP ) continue; //持ち駒を除く
		Piece piece = ptree->board[z];
		sq = z2sq[z];
		if( !( EMP < piece && piece <= ERY ) || !( sq < nsquare ) ) printf("Error_ev1\n");
		if( base_tbl[piece].f_pt == -1 ) printf("Error_ev2\n");
		pieceListFb[nlist] = base_tbl[piece].f_pt + sq;
		pieceListFw[nlist] = base_tbl[piece].e_pt + Inv(sq);
		nlist++;
	}

	if( nlist!=38 ) printf("nlist : %d\n",nlist);

	sum[0][0] = sum[0][1] = sum[1][0] = sum[1][1] = 0;

	//KK
	sum[2][0] = kk[sq_bk][sq_wk][0];
	sum[2][1] = kk[sq_bk][sq_wk][1];
	/*
	printf("KK[0]:%d\n",sum[2][0]);
	printf("KK[1]:%d\n",sum[2][1]);
	*/
	BonaPiece k0,k1,l0,l1;
	
	sum[2][0] += kkp[sq_bk][sq_wk][pieceListFb[0]][0];
	sum[2][1] += kkp[sq_bk][sq_wk][pieceListFb[0]][1];

	for ( i=1; i<38; ++i )
    {
		k0 = pieceListFb[i];
		k1 = pieceListFw[i];

		for( j=0; j<i; ++j )
        {
			l0 = pieceListFb[j];
			l1 = pieceListFw[j];
			sum[0][0] += kpp[sq_bk][k0][l0][0];
			sum[0][1] += kpp[sq_bk][k0][l0][1];
			sum[1][0] += kpp[Inv(sq_wk)][k1][l1][0];
			sum[1][1] += kpp[Inv(sq_wk)][k1][l1][1];
		}
		sum[2][0] += kkp[sq_bk][sq_wk][k0][0];
		sum[2][1] += kkp[sq_bk][sq_wk][k0][1];
	}

	sum[2][0] += material*FV_SCALE;
	sum[2][0] += material*FV_SCALE;
	/*
	printf("material:%d\n",material);
	printf("KKP[0]:%d\n",sum[2][0]);
	printf("KKP[1]:%d\n",sum[2][1]);
	printf("KPP[0][0]:%d\n",sum[0][0]);
	printf("KPP[1][0]:%d\n",sum[1][0]);
	printf("KPP[0][1]:%d\n",sum[0][1]);
	printf("KPP[1][1]:%d\n",sum[1][1]);
	*/
	
	scoreBoard = sum[0][0] - sum[1][0] + sum[2][0];
	scoreTurn  = sum[0][1] + sum[1][1] + sum[2][1];

	return ((( ptree->color == Black ? scoreBoard : -scoreBoard) + scoreTurn )/FV_SCALE );
	//return (( ptree->color == Black ? scoreBoard : -scoreBoard) /FV_SCALE );
}
