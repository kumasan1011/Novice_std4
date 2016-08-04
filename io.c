#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "define.h"
#include "io.h"

void PrintBoard( const struct Position *pos ){
	
	int i;
	int x,y;
	
	printf("    9   8   7   6   5   4   3   2   1 \n");
	printf(" +------------------------------------+");
	for( y=1; y<=9; y++ )
    {
		printf("\n |                                    |");
		printf("\n |");
		for( x=1; x<=9; x++ )
        {
			if( pos->board[SQ(x,y)]>=EFU )
            {
				printf(" %s ",PieceName2[pos->board[SQ(x,y)]-15]);
			}else{
				printf(" %s ",PieceName[pos->board[SQ(x,y)]]);
			}
		}
		printf("| %d",y);
	}
	printf("\n |                                    |");
	printf("\n +------------------------------------+\n");
	
	printf("  Black_Hand: ");
	for( i=1; i<8; i++ )
    {
		if( pos->b_hand[i]>0 )
        {
			if( pos->b_hand[i]==1 )
            {
				printf("%s ",PieceName[i]);
			}
            else
            {
				printf("%s-%d ",PieceName[i],pos->b_hand[i]);
			}
		}
	}
	printf("\n  White_Hand: ");
	for( i=1; i<8; i++ )
    {
		if(pos->w_hand[i]>0)
        {
			if(pos->w_hand[i]==1)
            {
				printf("%s ",PieceName[i]);
			}
            else
            {
				printf("%s-%d ",PieceName[i],pos->w_hand[i]);
			}
		}
	}
	printf( "\n  Color:%s\n", pos->color ? "White":"Black" );
	//printf( "Hash:%llx\n", pos->hashkey );
	//printf( "Is2FU_b : %x\n",pos->Is2FU_b);
	//printf( "Is2FU_w : %x\n",pos->Is2FU_w);
	printf("\n");
    /*
    //debug 
    for( i=1; i<=40; i++ )
    {
        printf("pieceNum:%d sq:%d black?:%d white?:%d \n",i,pos->piecePos[i],pos->pieceCol_b[i],pos->pieceCol_w[i]);
        
    }*/
}

void make_usi_position( const char *buf, struct Position* pos )
{
	int i,j,k;
	int n = 0;
	pos->color = Black;
	Move move=0;
	int len = strlen("position startpos moves ");
	
	if(strlen("position startpos")==strlen(buf)) return;
	
	for( i=len; i<strlen(buf); i++ )
	{
		
		move=0;
		
		if( buf[i]==' ' )
		{
			continue;
		}
		if( buf[i+1]=='*' )//Drop
		{ 
			for( j=1; j<8; j++ )
			{
				if( buf[i] == UsiPieceName1[j] )
				{
					move|=AddDrop(1);
					if( pos->color == Black )
					{
						move|=AddFrom(j);
					}
					else
					{
						move|=AddFrom(j+15);
					}
					break;
				}
			}
		}
		else //Move
		{ 
			int File,Rank,From;
			File=10-((buf[i]-'1')+1);
			Rank=((buf[i+1]-'a')+1);
			From=SQ(File,Rank);
			move|=AddFrom(From);
		}
		
		int To_File,To_Rank,To;
		To_File=10-((buf[i+2]-'1')+1);
		To_Rank=((buf[i+3]-'a')+1);
		To=SQ(To_File,To_Rank);
		move|=AddTo(To);
		
		if( pos->board[To] )
		{
			move|=AddCap( pos->board[To] );
		}
		
		if( buf[i+4]=='+' )
		{
			move|=AddPro(1);
			i+=4;
		}
		else
		{
			i+=3;
		}
		
		doMove( pos , move );
		pos->color = 1 - pos->color;
	}
}

void make_sfen_position( const char *buf, struct Position* pos )
{
	
	int i,j,k;
	int n = 0;
	
	int len = strlen("position sfen ");
	
	int x=1,y=1; /* x:FILE y:RANK */
	bool promote=false;
	
	for( i=len; i<strlen(buf); i++ )
	{
		if(buf[i]==' ') break;
		/* if EMPTY */
		if( buf[i]>='1' && buf[i]<='9' )
		{
			int num,end=1+(buf[i]-'1');
			for( num=x; num<x+end; num++ )
			{
				pos->board[SQ(num,y)]=EMP;
			}
			x+=end;
		}
		else if( buf[i]=='/' )
		{
			x=1;
			y++;
		}
		else if( buf[i]=='+' )
		{
			promote=true;
		}
		else
		{
			for( j=1; j<=8; j++ )
			{
				if(buf[i] == UsiPieceName1[j])
				{
					pos->board[ SQ(x,y) ] = j;
					if( promote ) pos->board[ SQ(x,y) ] += 0x08;
					promote=false;
					x++;
					break;
				}
				else if( buf[i] == UsiPieceName2[j] )
				{
					pos->board[ SQ(x,y) ] = j + 15;
					if( promote ) pos->board[SQ(x,y)] += 0x08;
					promote=false;
					x++;
					break;
				}
			}
		}
	}
	
	if(buf[i+1]=='b'){
		pos->color = Black;
	}else if(buf[i+1]=='w'){
		pos->color = White;
	}
	
	for( j=i+3; j<strlen(buf); j++ )
	{
		if(buf[j]==' ') break;
		if( buf[j]>='1' && buf[j]<='9' )
		{
			int num=1+(buf[j]-'1');
			j++;
			for( k=1; k<8; k++ )
			{
				if( buf[j] == UsiPieceName1[k] )
				{
					pos->b_hand[k]=num;
					pos->b_hand[0]+=num;
					break;
				}
				else if( buf[j] == UsiPieceName2[k] )
				{
					pos->w_hand[k]=num;
					pos->w_hand[0]+=num;
					break;
				}
			}
		}
		else
		{
			for( k=1; k<8; k++ )
			{
				if( buf[j] == UsiPieceName1[k] )
				{
					pos->b_hand[k] = 1;
					pos->b_hand[0] += 1;
					break;
				}
				else if( buf[j] == UsiPieceName2[k] )
				{
					pos->w_hand[k] = 1;
					pos->w_hand[0] += 1;
					break;
				}
			}
		}
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
	
	//駒番号を設定
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SOU ){ pos->piecePos[1] = x; }
        if( pos->board[x]==EOU ){ pos->piecePos[2] = x; }
    }
    n=3;
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SHI || pos->board[x]==EHI || pos->board[x]==SRY || pos->board[x]==ERY )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<5 ){ pos->piecePos[n] = 0;  pos->pieceStock[HI][0]++; pos->pieceStock[HI][pos->pieceStock[HI][0]]=n; n++; }
    
    for( x=0; x<256; x++ )
    {
        if( pos->board[x]==SKA || pos->board[x]==EKA || pos->board[x]==SUM || pos->board[x]==EUM )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<7 ){ pos->piecePos[n] = 0; pos->pieceStock[KA][0]++; pos->pieceStock[KA][pos->pieceStock[KA][0]]=n; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SKI || pos->board[x]==EKI )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<11 ){ pos->piecePos[n] = 0; pos->pieceStock[KI][0]++; pos->pieceStock[KI][pos->pieceStock[KI][0]]=n; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SGI || pos->board[x]==EGI || pos->board[x]==SNG || pos->board[x]==ENG )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<15 ){ pos->piecePos[n] = 0; pos->pieceStock[GI][0]++; pos->pieceStock[GI][pos->pieceStock[GI][0]]=n; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SKE || pos->board[x]==EKE || pos->board[x]==SNE || pos->board[x]==ENE )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<19 ){ pos->piecePos[n] = 0; pos->pieceStock[KE][0]++; pos->pieceStock[KE][pos->pieceStock[KE][0]]=n; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SKY || pos->board[x]==EKY || pos->board[x]==SNY || pos->board[x]==ENY )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<23 ){ pos->piecePos[n] = 0; pos->pieceStock[KY][0]++; pos->pieceStock[KY][pos->pieceStock[KY][0]]=n; n++; }
    
    for( x=0; x<256; x++ )
    { 
        if( pos->board[x]==SFU || pos->board[x]==EFU || pos->board[x]==STO || pos->board[x]==ETO )
        { pos->piecePos[n] = x; n++; }
    }
    while( n<=40 ){ pos->piecePos[n] = 0; pos->pieceStock[FU][0]++; pos->pieceStock[FU][pos->pieceStock[FU][0]]=n; n++; }
    
    //駒番号と色
	/*
    for( x=1; x<=40; x++ )
    {
        pos->pieceCol_b[x] = pos->pieceCol_w[x] = 0;
        if( SFU <= pos->board[ pos->piecePos[x] ] && pos->board[ pos->piecePos[x] ] <= SRY )
        { pos->pieceCol_b[x] = 1; }
        if( EFU <= pos->board[ pos->piecePos[x] ] && pos->board[ pos->piecePos[x] ] <= ERY )
        { pos->pieceCol_w[x] = 1; }
    }
	*/
	for( y=1; y<=9; y++ )
    {
        for( x=1; x<=9; x++ )
        {
            Board sq = SQ( x, y );
            if(  SFU <= pos->board[sq] && pos->board[sq] <= SRY ){ pos->boardCol_b[sq]=1; }
			else { pos->boardCol_b[sq]=0; }
            if(  EFU <= pos->board[sq] && pos->board[sq] <= ERY ){ pos->boardCol_w[sq]=1; }
			else { pos->boardCol_w[sq]=0; }
        }
    }
	
	for( x=1; x<=40; x++)
    {
        if( pos->piecePos[x] )
        {
            pos->boardNum[ pos->piecePos[x] ] = x;
        }
    }
	
}

void PrintAllMoves( Move* move, int num )
{
	int i,From,To,Koma;
	for( i=0; i<num; i++ )
	{
		if( GetDrop(move[i]) )
		{
			From = 0;
		}
		else
		{
			From = GetFrom(move[i]);
		}
		
		To = GetTo(move[i]);
		
		if( GetPro(move[i]) )
		{
			printf("%d%d+ ", NSQ(From), NSQ(To) );
		}
		else if( !From )
		{
			printf("%d%d* ", GetFrom(move[i]) ,NSQ(To) );
		}
		else
		{
			printf("%d%d  ", NSQ(From) ,NSQ(To) );
		}
	}
}

void PrintColor( struct Position *pos )
{
	int x,y,sq;
	for( y=1; y<=9; y++ )
	{
		for( x=1; x<=9; x++ )
		{
			sq = SQ(x,y);
			if( pos->boardCol_b[sq] )
			{
				printf("[X]");
			}
			else
			{
				printf("[ ]");
			}
		}
		printf("\n");
	}
	
	for( y=1; y<=9; y++ )
	{
		for( x=1; x<=9; x++ )
		{
			sq = SQ(x,y);
			if( pos->boardCol_w[sq] )
			{
				printf("[X]");
			}
			else
			{
				printf("[ ]");
			}
		}
		printf("\n");
	}
}

void send_best_to_usi( Move move )
{	
	int To = GetTo(move);
	int From = GetFrom(move);  
	int Drop = GetDrop(move);
	int Pro = GetPro(move); 
	
	if(Drop){
		if( From>=EFU ) From-=15;
		printf("bestmove %s*%d%s",UsiPieceName[From],10-To%16,RankName[To/16]);
	}else{
		printf("bestmove %d%s%d%s",10-From%16,RankName[From/16],10-To%16,RankName[To/16]);
		if(Pro) printf("+");
	}
	printf("\n");
}

void printAllMoves( Move *move, int moveNum )
{
	int i;
	for( i=0; i<moveNum; i++ )
	{
		Board From = GetFrom( move[i] );
		Board To = GetTo( move[i] );
		Board Pro = GetPro( move[i] );
		Piece Cap = GetCap( move[i] );
		
        printf("From : %d ", NSQ(From) );
        printf("To : %d ", NSQ(To) );
        printf("Cap : %d\n", Cap );
	}
}