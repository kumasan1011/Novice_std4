#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "define.h"
#include "check.h"

int Direct[8]={
	-15,-16,-17,-1,1,17,16,15
};

int CanGo[8][31]={
	{   //-15
		//p,l,n,s,g,b,r,k,g,g,g,g,x,b,r
		0,0,0,0,1,1,0,0,1,1,1,1,1,0,0,1,
		  0,0,0,1,0,0,0,1,0,0,0,0,0,0,1
	},{ //-16
		//p,l,n,s,g,b,r,k,g,g,g,g,x,b,r
		0,1,0,0,1,1,0,0,1,1,1,1,1,0,1,0,
		  0,0,0,0,1,0,0,1,1,1,1,1,0,1,0
	},{ //-17
		//p,l,n,s,g,b,r,k,g,g,g,g,x,b,r
		0,0,0,0,1,1,0,0,1,1,1,1,1,0,0,1,
		  0,0,0,1,0,0,0,1,0,0,0,0,0,0,1
	},{ //-1
		//p,l,n,s,g,b,r,k,g,g,g,g,x,b,r
		0,0,0,0,0,1,0,0,1,1,1,1,1,0,1,0,
		  0,0,0,0,1,0,0,1,1,1,1,1,0,1,0
	},{ //+1
		//p,l,n,s,g,b,r,k,g,g,g,g,x,b,r
		0,0,0,0,0,1,0,0,1,1,1,1,1,0,1,0,
		  0,0,0,0,1,0,0,1,1,1,1,1,0,1,0
	},{ //+17
		//p,l,n,s,g,b,r,k,g,g,g,g,x,b,r
		0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,
		  0,0,0,1,1,0,0,1,1,1,1,1,0,0,1
		
	},{ //+16
		//p,l,n,s,g,b,r,k,g,g,g,g,x,b,r
		0,0,0,0,0,1,0,0,1,1,1,1,1,0,1,0,
		  1,0,0,1,1,0,0,1,1,1,1,1,0,1,0
		
	},{ //+15
		//p,l,n,s,g,b,r,k,g,g,g,g,x,b,r
		0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,
		  0,0,0,1,1,0,0,1,1,1,1,1,0,0,1
		
	}
};


int is_check_from_bishop(struct Position *pos,int dir,Board sq)
{	
	int i;
	sq+=dir;
	switch( pos->color )
    {
        case Black: 
		for( i=0; i<9; i++ )
        {
			if( pos->board[sq]==EKA || pos->board[sq]==EUM ) return 1;
			else if( pos->board[sq] ) return 0;
			sq+=dir;
		}
        break;

        case White:
		for( i=0; i<9; i++ )
        {
			if( pos->board[sq]==SKA || pos->board[sq]==SUM ) return 1;
			else if( pos->board[sq] ) return 0;
			sq+=dir;
		}
        break;
	}	
	return 0;
}

int is_check_from_rook(struct Position *pos,int dir,Board sq)
{	
	int i;
	sq+=dir;
	switch( pos->color )
    {
        case Black:
		for( i=0; i<9; i++ )
        {
			if( pos->board[sq]==EHI || pos->board[sq]==ERY ) return 1;
			else if( pos->board[sq] ) return 0;
			sq+=dir;
		}
        break;

        case White:
		for( i=0; i<9; i++ )
        {
			if( pos->board[sq]==SHI || pos->board[sq]==SRY ) return 1;
			else if( pos->board[sq] ) return 0;
			sq+=dir;
		}
        break;
	}
	
	return 0;
}

int is_check_from_lance(struct Position *pos,int dir,Board sq)
{	
	int i;
	sq+=dir;
	switch( pos->color )
    {
        case Black:
		for( i=0; i<9; i++ )
        {
			if( pos->board[sq]==EKY ) return 1;
			else if( pos->board[sq] ) return 0;
			sq+=dir;
		}
        break;

	    case White:
		for( i=0; i<9; i++ )
        {
			if( pos->board[sq]==SKY ) return 1;
			else if( pos->board[sq] ) return 0;
			sq+=dir;
		}
        break;
	}
	
	return 0;
}

int is_check_from_normal( struct Position *pos, Board sq )
{	
	int i;
	
    switch( pos->color )
    {
	    case Black:
		for(i=0;i<8;i++)
        {
			if( pos->boardCol_w[sq+Direct[i]] )
            {
				if( CanGo[7-i][pos->board[sq+Direct[i]]]==1 ) return 1;
			}
		}
		if( pos->board[sq-31]==EKE || pos->board[sq-33]==EKE ) return 1;
        break;
	
        case White:
		for(i=0;i<8;i++){
			if( pos->boardCol_b[sq+Direct[i]] )
            {
				if( CanGo[7-i][pos->board[sq+Direct[i]]]==1 ) return 1;
			}
		}
		if( pos->board[sq+31]==SKE || pos->board[sq+33]==SKE ) return 1;
        break;
	}
	return 0;
}

int is_in_check( struct Position *pos )
{	
	int sq,i,j;
	
	sq=(pos->color? (pos->piecePos[2]):(pos->piecePos[1]));
	
	if(is_check_from_normal( pos, sq )) return 1;
	
	if(is_check_from_bishop( pos, -15, sq )) return 1;
	if(is_check_from_bishop( pos,  15, sq )) return 1;
	if(is_check_from_bishop( pos, -17, sq )) return 1;
	if(is_check_from_bishop( pos,  17, sq )) return 1;
	if(is_check_from_rook(   pos,  16, sq )) return 1;
	if(is_check_from_rook(   pos, -16, sq )) return 1;
	if(is_check_from_rook(   pos,   1, sq )) return 1;
	if(is_check_from_rook(   pos,  -1, sq )) return 1;
	
	if( pos->color==Black){ if(is_check_from_lance( pos, -16, sq )) return 1; }
	else { if(is_check_from_lance( pos, 16, sq )) return 1; }
	
	return 0;
}