#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "define.h"

void copyPosStruct( struct Position pos, struct Position* pos0 )
{
    int i,x,y;
    
    for( i=0; i<256; i++ )
    {
        pos0->board[i]     = pos.board[i];
        pos0->boardNum[i]  = pos.boardNum[i];
        pos0->boardCol_b[i]= pos.boardCol_b[i];
        pos0->boardCol_w[i]= pos.boardCol_w[i];
    }
    
    for( i=0; i<8; i++ )
    {
        pos0->w_hand[i] = pos.w_hand[i];
        pos0->b_hand[i] = pos.b_hand[i];
    }
    
    for( i=0; i<64; i++ )
    {
        pos0->piecePos[i] = pos.piecePos[i];
    }
    
    for( x=0; x<8; x++ )
    {
        for( y=0; y<32; y++ )
        {
            pos0->pieceStock[x][y] = pos.pieceStock[x][y];
        }
    }
    
    pos0->Is2FU_b = pos.Is2FU_b;
    pos0->Is2FU_w = pos.Is2FU_w;
    pos0->color   = pos.color;
    
}

void confPosStruct( struct Position pos, struct Position pos0 )
{
    int i,x,y;
    
     for( i=0; i<256; i++ )
    {
        if( pos0.board[i] != pos.board[i] ) printf("Error\n");
        if( pos0.boardNum[i] != pos.boardNum[i] ) printf("Error\n");
        if( pos0.boardCol_b[i] != pos.boardCol_b[i] ) printf("Error\n");
        if( pos0.boardCol_w[i] != pos.boardCol_w[i] ) printf("Error\n");
    }
    
    for( i=0; i<8; i++ )
    {
        if( pos0.w_hand[i] != pos.w_hand[i] ) printf("Error\n");
        if( pos0.b_hand[i] != pos.b_hand[i] ) printf("Error\n");
    }
    
    for( i=0; i<64; i++ )
    {
        if( pos0.piecePos[i] != pos.piecePos[i] ) printf("Error\n");
    }
    
    for( x=0; x<8; x++ )
    {
        for( y=0; y<32; y++ )
        {
            if( pos0.pieceStock[x][y] != pos.pieceStock[x][y] ) printf("Error\n");
        }
    }
    
    if( pos0.Is2FU_b != pos.Is2FU_b ) printf("Error\n");
    if( pos0.Is2FU_w != pos.Is2FU_w ) printf("Error\n");
    if( pos0.color   != pos.color   ) printf("Error\n");
}

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

Move d_move( struct Position* pos )
{
    int x,y,from,to,drop;
    //入力をもらう
    printf("drop?? (Yes=1:No=0)\n");
    if( scanf( "%d", &drop ) == 1 ) printf("OK\n");
    else printf("Error\n");
    
    printf("From\n");
    if( scanf( "%d", &from ) == 1 ) printf("OK\n");
    else printf("Error\n");
    Board From;
    if( drop == 0 )
    {
        From = SQ( (10-from/10), from%10 );
        printf("pos:%d\n",NSQ(From));
    }
    else
    {
        From = from;
    }
   
   
    printf("To\n");
    if( scanf( "%d", &to ) == 1 ) printf("OK\n");
    else printf("Error\n");
    Board To = SQ( (10-to/10), to%10 );
    printf("pos:%d\n",NSQ(To));
    
    Move move[600]; 
    move[0] = AddFrom(From) | AddTo(To);
    if( drop==1 )
    {
        move[0]|=AddDrop(1);
    }
    printf( "move:%d\n", move[0] );
    doMove( pos, &move[0] );
    
    return move[0];
}

void debugSearch( struct Position *pos, int depth )
{
    if( depth <= 0 ) return;

    int n;
    unsigned int move[768];
    int move_num=0x00;

    move_num += GenMoves( pos, &move[move_num] );
    //printAllMoves( &move[0], move_num );
    //scanf("%d",&n);
    int i;
    for( i=0; i<move_num; i++ )
    {
        doMove( pos, move[i] );
        //PrintBoard( pos );
        //scanf("%d",&n);
        pos->color = 1 - pos->color; 
        debugSearch( pos, depth-1 );
        pos->color = 1 - pos->color; 
        undoMove( pos, move[i] );
    }
}

void debugRule( struct Position *pos, Move move ) 
{
    int x,y;
    int n;
    Board sq;

    Board From = GetFrom( move );
    Board To = GetTo( move );
    Board Pro = GetPro( move );
    Piece Cap = GetCap( move );

    for( y=1; y<=9; y++ )
    {
        for( x=1; x<=9; x++ )
        {
            sq=SQ(x,y);
            if( SFU <= pos->board[sq] && pos->board[sq] <= SRY )
            {
                if( !pos->boardCol_b[sq] ) printf("Error 1\n");
                if(  pos->boardCol_w[sq] ) printf("Error 2\n");
            }
            else if( EFU <= pos->board[sq] && pos->board[sq] <= ERY )
            {
                if(  pos->boardCol_b[sq] ) 
                {
                    printf("Error 3 sq = %d\n",sq);
                    printf("Error\n");
                    printf("board[To] : %d ", pos->board[To] );
                    printf("Piece : %d ", pos->board[From] );
                    printf("From : %d ", NSQ(From) );
                    printf("To : %d ", NSQ(To) );
                    printf("Cap : %d\n", Cap );
                    PrintBoard(*pos);
                    //scanf("%d",&n);
                }
                if( !pos->boardCol_w[sq] ) printf("Error 4\n");
            }
            else if( !pos->board[sq] )
            {
                if(  pos->boardCol_b[sq] )
                {
                    printf("Error 5 sq = %d\n",sq);
                    printf("Error\n");
                    printf("board[To] : %d ", pos->board[To] );
                    printf("Piece : %d ", pos->board[From] );
                    printf("From : %d ", NSQ(From) );
                    printf("To : %d ", NSQ(To) );
                    printf("Cap : %d\n", Cap );
                    PrintBoard(*pos);
                    //scanf("%d",&n);
                }
                if(  pos->boardCol_w[sq] ) printf("Error 6\n");
            }
        } 
    }
}

void debugHashMoves( struct Position *pos )
{
    int n;
    unsigned int move[768];
    int move_num=0x00;

    move_num += GenMoves( pos, &move[move_num] );
    //printAllMoves( &move[0], move_num );
    //scanf("%d",&n);
    int i;
    for( i=0; i<move_num; i++ )
    {
        PrintBoard( *pos );
        doMove( pos, move[i] );
        PrintBoard( *pos );
        undoMove( pos, move[i] );
        PrintBoard( *pos );
        //scanf("%d",&n);
    }
}