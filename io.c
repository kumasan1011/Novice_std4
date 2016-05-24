#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "define.h"

void PrintBoard( struct Position pos ){
	
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
			if( pos.board[SQ(x,y)]>=EFU )
            {
				printf(" %s ",PieceName2[pos.board[SQ(x,y)]-15]);
			}else{
				printf(" %s ",PieceName[pos.board[SQ(x,y)]]);
			}
		}
		printf("| %d",y);
	}
	printf("\n |                                    |");
	printf("\n +------------------------------------+\n");
	
	printf("  Black_Hand: ");
	for( i=1; i<8; i++ )
    {
		if( pos.b_hand[i]>0 )
        {
			if( pos.b_hand[i]==1 )
            {
				printf("%s ",PieceName[i]);
			}
            else
            {
				printf("%s-%d ",PieceName[i],pos.b_hand[i]);
			}
		}
	}
	printf("\n  White_Hand: ");
	for( i=1; i<8; i++ )
    {
		if(pos.w_hand[i]>0)
        {
			if(pos.w_hand[i]==1)
            {
				printf("%s ",PieceName[i]);
			}
            else
            {
				printf("%s-%d ",PieceName[i],pos.w_hand[i]);
			}
		}
	}
	printf( "\n  Color:%s\n", pos.color ? "White":"Black" );
	printf( "Hash:%llx\n", pos.hashkey );
	printf("\n");
}