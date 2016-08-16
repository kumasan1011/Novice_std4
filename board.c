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


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "define.h"
#include "board.h"

short pc_on_sq[nsquare][pos_n];
short pc_on_sq2[nsquare][fe_end * (fe_end + 1)];
short kkp[nsquare][nsquare][kkp_end];

Hash zobrist[Piece_NB][SQ_NB];
Hash zobHand[Color_NB][Hand_NB];

struct Position tree;

void InitBoard(struct Position* pos)
{
    int x,y;
    
    for( x=0; x<256; x++ )
    {
        pos->board[x] = WAL;
        pos->boardCol_b[x] = pos->boardCol_w[x] = 0 ;
        pos->boardNum[x] = 0;
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
		{ WAL,SKY,SKE,SGI,SKI,SOU,SKI,SGI,SKE,SKY }
	};
    
    for( y=1; y<=9; y++ )
    {
        for( x=1; x<=9; x++ )
        {
            Board sq = SQ( x, y );
            pos->board[sq] = StartPos[y][x];
            if(  SFU <= pos->board[sq] && pos->board[sq] <= SRY ){ pos->boardCol_b[sq]=1; }
            if(  EFU <= pos->board[sq] && pos->board[sq] <= ERY ){ pos->boardCol_w[sq]=1; }
        }
    }
    
    for( x=0; x<8; x++ )
    {
        pos->b_hand[x] = pos->w_hand[x] = 0;
    }
    
    pos->Is2FU_b = pos->Is2FU_w = 0;
	for( x=1; x<=9; x++ )
	{
		for( y=1; y<=9; y++ )
		{
			if( pos->board[SQ(x,y)]==SFU ) pos->Is2FU_b|=(1<<(10-x));
			if( pos->board[SQ(x,y)]==EFU ) pos->Is2FU_w|=(1<<(10-x));
		}
	}
    
    for( x=0; x<8; x++ )
	{
		for( y=0; y<32; y++ )
		{
			pos->pieceStock[x][y]=0;
		}
	}
    
    //駒番号を設定
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SOU ){ pos->piecePos[1] = x; }
        if( pos->board[x]==EOU ){ pos->piecePos[2] = x; }
    }
    int n=3;
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SHI || pos->board[x]==EHI || pos->board[x]==SRY || pos->board[x]==ERY )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<5 ){ pos->piecePos[n] = 0; n++; }
    
    for( x=0; x<256; x++ )
    {
        if( pos->board[x]==SKA || pos->board[x]==EKA || pos->board[x]==SUM || pos->board[x]==EUM )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<7 ){ pos->piecePos[n] = 0; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SKI || pos->board[x]==EKI )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<11 ){ pos->piecePos[n] = 0; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SGI || pos->board[x]==EGI || pos->board[x]==SNG || pos->board[x]==ENG )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<15 ){ pos->piecePos[n] = 0; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SKE || pos->board[x]==EKE || pos->board[x]==SNE || pos->board[x]==ENE )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<19 ){ pos->piecePos[n] = 0; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SKY || pos->board[x]==EKY || pos->board[x]==SNY || pos->board[x]==ENY )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<23 ){ pos->piecePos[n] = 0; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SFU || pos->board[x]==EFU || pos->board[x]==STO || pos->board[x]==ETO )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<=40 ){ pos->piecePos[n] = 0; n++; }
    
    //駒番号と色
    /*for( x=1; x<=40; x++ )
    {
        pos->pieceCol_b[x] = pos->pieceCol_w[x] = 0;
        if( SFU <= pos->board[ pos->piecePos[x] ] && pos->board[ pos->piecePos[x] ] <= SRY )
        { pos->pieceCol_b[x] = 1; }
        if( EFU <= pos->board[ pos->piecePos[x] ] && pos->board[ pos->piecePos[x] ] <= ERY )
        { pos->pieceCol_w[x] = 1; }
    }*/
    
    for( x=1; x<=40; x++)
    {
        if( pos->piecePos[x] )
        {
            pos->boardNum[ pos->piecePos[x] ] = x;
        }
    }
    
    pos->color = Black; 
    
    pos->hashkey = calHash( *pos );
    // for debug
    //pos->color = White; 
}

int load_fv(){
	
	FILE *fp;
	size_t size;
	
	fp = fopen( "fv.bin" , "rb" );
	if ( fp == NULL ) { return -2; }
	
	size = nsquare * pos_n;
	if( fread( pc_on_sq, sizeof(short), size, fp ) != size ){
		fclose( fp );
		return -2;
	}
	
	size = nsquare * nsquare * kkp_end;
	if ( fread( kkp, sizeof(short), size, fp ) != size ){
		fclose( fp );
		return -2;
    }
	
	fclose( fp );
	
	int i,j,k;
	
	for( k=0; k<nsquare; k++ ){
		for( i=0; i<fe_end; i++ ){
			for( j=0; j<fe_end; j++ ){
				if( j<=i ){
					PcPcOnSq2(k, i, j) = PcPcOnSq(k, i, j);
				}else{
					PcPcOnSq2(k, i, j) = PcPcOnSq(k, j, i);
				}
			}
		}
	}
	return 0;
}

// XOR疑似乱数
unsigned long xor128_() {
    static unsigned long x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned long t;
    t=(x^(x<<11));
	x=y;y=z;z=w; 
	return( w=(w^(w>>19))^(t^(t>>8)) );
}

// 64bit乱数の生成
uint64 xor128(){
	
	return xor128_() + (xor128_() << 31);
	
}

void initHash()
{
    int j,k;

    for( j = 0; j < Piece_NB; j++ )
    {
        for( k = 0; k < SQ_NB; k++ )
        {
            zobrist[j][k] = xor128() << 1;
            // 左に1bitずらして手番を入れる  先手：０　後手：１
        }
    }

    for( j = 0; j < Color_NB; j++ )
    {
        for( k = 0; k < Hand_NB; k++ )
        {
            zobHand[j][k] = xor128() << 1;
        }
    }
}

Hash calHash( struct Position pos )
{
    Hash result = 0;
    int x,y,z;

    for( y=1; y<=9; y++ )
    {
        for( x=1; x<=9; x++ )
        {
            z = SQ(x,y);
            if( pos.board[z] )
            {
                result += zobrist[ pos.board[z] ][z];
            }
        }
    }

    for( x = 1; x < Hand_NB; x++ )
    {
        result += zobHand[Black][x] * pos.b_hand[x];
        result += zobHand[White][x] * pos.w_hand[x];
    }

    if( pos.color == White ) result ^= 1;

    return result;
}