#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "define.h"

void DoMove( struct Position* pos, Move& move )
{
    int To = GetTo(move);
    
    if( GetDrop(move) )
    {
        pos->board[ To ] = GetFrom(move);
        if( pos->color ){ pos->boardCol_b[ To ] = 1; }
        else { pos->boardCol_w[ To ] = 1; }
    }
    else
    {
        int Cap = pos->board[ To ];
        move |= AddCap(Cap);
        pos->board[ To ] = pos->board[ From ];
        pos->board[ From ] = EMP;
        if( GetPro(move) )
        {
            pos->board[ To ] += 0x08 ;
        }
    }
}

void UndoMove( struct Position* pos, Move* move )
{
    
}