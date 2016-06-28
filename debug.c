#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "define.h"

void d_setPos( struct Position pos )
{
    int x,y,i;
    Board sq;
    //局面の色と駒が一致しているか
    for( x=1; x<=9; x++ )
    {
        for( y=1; y<=9; y++ )
        {
            sq = SQ(x,y);
            if( pos.board[sq] != EMP )
            {
                if( pos.board[sq] != pos.board[ pos.piecePos[ pos.boardNum[sq] ] ] )
                {
                    printf( "Error-1( %d )\n", NSQ(sq) );
                }
                
                if( 
                    ( pos.boardCol_b[sq] && ( SFU<=pos.board[sq] && pos.board[sq]<=SRY ) ) 
                 || ( pos.boardCol_w[sq] && ( EFU<=pos.board[sq] && pos.board[sq]<=ERY ) )
                ) { continue; }
                else
                {
                    printf( "Error-2( %d )\n", NSQ(sq) );
                }
                
            }
        }
    }
}

void d_move( struct Position* pos )
{
    int x,y,from,to;
    //入力をもらう
    printf("From\n");
    if( scanf( "%d", &from ) == 0 ) printf("OK\n");
    else printf("Error\n");
    Board From = SQ( (10-from/10), from%10 );
    printf("pos:%d\n",NSQ(From));
   
    printf("To\n");
    if( scanf( "%d", &to ) == 0 ) printf("OK\n");
    else printf("Error\n");
    Board To = SQ( (10-to/10), to%10 );
    printf("pos:%d\n",NSQ(To));
    
    Move move[600]; 
    move[0] = AddFrom(From) | AddTo(To);
    printf( "move:%d\n", move[0] );
    doMove( pos, &move[0] );
   
}