#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "define.h"
#include "genmove.h"

int GenPawnMove_b( struct Position* pos, Board sq , Move* move )
{
    Board To = sq - 16;
    
    if( !pos->boardCol_b[To] )
    {
        move[0] = AddTo(To) | AddFrom(sq);
        if( To<0x40 ) //成り
        {
            move[0] |= AddPro(1);
        }
        return 1;
    }
}

int GenPawnMove_w( struct Position* pos, Board sq , Move* move )
{
    Board To = sq + 16;
    
    if( !pos->boardCol_w[To] )
    {
        move[0] = AddTo(To) | AddFrom(sq);
        if( To>0x70 ) //成り
        {
            move[0] |= AddPro(1);
        }
        return 1;
    }
}

int GenLanceMove_b()
{
    
}

int GenLanceMove_w()
{
    
}

int GenKnightMove_b()
{
    
}

int GenKnightMove_w()
{
    
}

int GenSilverMove_b()
{
    
}

int GenSilverMove_w()
{
    
}

int GenGoldMove_b()
{
    
}

int GenGoldMove_w()
{
    
}

int GenBishopMove_b()
{
    
}

int GenBishopMove_w()
{
    
}

int GenRookMove_b()
{
    
}

int GenRookMove_w()
{
    
}



int GenMove( struct Position* pos, Move* move)
{
    int i;
    int moveNum = 0;
    
    switch( pos->color )
    {    
        case Black:
        for( i=1; i<=40; i++ )
        {
            if( pos->pieceCol_b[i] )
            {
                switch( pos->board[ pos->piecePos[i] ] )
                {
                    case SFU:
                    moveNum += GenPawnMove_b( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case SKY:
                    break;
                    case SKE:
                    break;
                    case SGI:
                    break;
                    case SKI: case STO: case SNY: case SNE: case SNG:
                    break;
                    case SOU:
                    break;
                    case SKA:
                    break;
                    case SHI:
                    break;
                    case SUM:
                    break;
                    case SRY:
                    break;
                }
            }
        }
        break;
        
        case White:
        for( i=1; i<=40; i++ )
        {
            if( pos->pieceCol_w[i] )
            {
                switch( pos->board[ pos->piecePos[i] ] )
                {
                    case EFU:
                    break;
                    case EKY:
                    break;
                    case EKE:
                    break;
                    case EGI:
                    break;
                    case EKI: case ETO: case ENY: case ENE: case ENG:
                    break;
                    case EOU:
                    break;
                    case EKA:
                    break;
                    case EHI:
                    break;
                    case EUM:
                    break;
                    case ERY:
                    break;
                }
            }
        }
        break;
    }
    return moveNum; 
}