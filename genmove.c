#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "define.h"

int GenMove(const struct Position pos)
{
    int i;
    
    switch( pos.color ){
        
        case black:
        for( i=1; i<=40; i++ )
        {
            if( !pos.pieceCol[i] )
            {
                switch( pos.board[ pos.piecePos[i] ] )
                {
                    case SFU:
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
        
        case white:
        for( i=1; i<=40; i++ )
        {
            if( pos.pieceCol[i] )
            {
                switch( pos.board[ pos.piecePos[i] ] )
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
}