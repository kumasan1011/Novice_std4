#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "define.h"
#include "genmove.h"

inline int GenPawnMove_b( struct Position* pos, Board sq , Move* move )
{
    Board To = sq - 16;
    
    if( !pos->boardCol_b[To] )
    {
        move[0] = AddTo(To) | AddFrom(sq);
        if( To<0x40 || sq<0x40 ) //成り
        {
            move[0] |= AddPro(1);
        }
        return 1;
    }
}

inline int GenPawnMove_w( struct Position* pos, Board sq , Move* move )
{
    Board To = sq + 16;
    
    if( !pos->boardCol_w[To] )
    {
        move[0] = AddTo(To) | AddFrom(sq);
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[0] |= AddPro(1);
        }
        return 1;
    }
}

inline int GenLanceMove_b( struct Position* pos, Board sq , Move* move )
{
    Board To;
    int i,num=0;
    
    for( i=1; i<10; i++ )
    {
        To = sq - (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                if( To<0x30 )
                {
                    move[num-1] |= AddPro(1);
                }
                else
                {
                    move[num] = AddTo(To) | AddFrom(sq);
                    move[num] |= AddPro(1);
                    num++;
                }
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                if( To<0x30 )
                {
                    move[num-1] |= AddPro(1);
                }
                else
                {
                    move[num] = AddTo(To) | AddFrom(sq);
                    move[num] |= AddPro(1);
                    num++;
                }
            }
            break;
        }
        else 
        {
            break;
        }
    }
    
    return num;
}

inline int GenLanceMove_w( struct Position* pos, Board sq , Move* move )
{
    Board To;
    int i,num=0;
    
    for( i=1; i<10; i++ )
    {
        To = sq + (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                if( To>0x80 )
                {
                    move[num-1] |= AddPro(1);
                }
                else
                {
                    move[num] = AddTo(To) | AddFrom(sq);
                    move[num] |= AddPro(1);
                    num++;
                }
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                if( To>0x80 )
                {
                    move[num-1] |= AddPro(1);
                }
                else
                {
                    move[num] = AddTo(To) | AddFrom(sq);
                    move[num] |= AddPro(1);
                    num++;
                }
            }
            break;
        }
        else
        {
            break;
        }
    }
    
    return num;
}

inline int GenKnightMove_b( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq - 31;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To<0x40 || sq<0x40 ) //成り
        {
            if( To<0x30 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num] = AddTo(To) | AddFrom(sq);
                move[num] |= AddPro(1);
                num++;
            }
        }
    }
    
    To = sq - 33;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To<0x40 || sq<0x40 ) //成り
        {
            if( To<0x30 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num] = AddTo(To) | AddFrom(sq);
                move[num] |= AddPro(1);
                num++;
            }
        }
    }
    
    return num;
}

inline int GenKnightMove_w( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq + 31;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To>0x70 || sq>0x70 ) //成り
        {
            if( To>0x80 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num] = AddTo(To) | AddFrom(sq);
                move[num] |= AddPro(1);
                num++;
            }
        }
    }
    
    To = sq + 33;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To>0x70 || sq>0x70 ) //成り
        {
            if( To>0x80 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num] = AddTo(To) | AddFrom(sq);
                move[num] |= AddPro(1);
                num++;
            }
        }
    }
    
    return num;
}

inline int GenSilverMove_b( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq - 15;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num] = AddTo(To) | AddFrom(sq);
             move[num] |= AddPro(1);
             num++;
        }
    }
    
    To = sq - 16;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num] = AddTo(To) | AddFrom(sq);
             move[num] |= AddPro(1);
             num++;
        }
    }
    
    To = sq - 17;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num] = AddTo(To) | AddFrom(sq);
             move[num] |= AddPro(1);
             num++;
        }
    }
    
    To = sq + 15;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num] = AddTo(To) | AddFrom(sq);
             move[num] |= AddPro(1);
             num++;
        }
    }
    
    To = sq + 17;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num] = AddTo(To) | AddFrom(sq);
             move[num] |= AddPro(1);
             num++;
        }
    }
    
    return num;
}

inline int GenSilverMove_w( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq + 15;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num] = AddTo(To) | AddFrom(sq);
            move[num] |= AddPro(1);
            num++;
        }
    }
    
    To = sq + 16;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num] = AddTo(To) | AddFrom(sq);
            move[num] |= AddPro(1);
            num++;
        }
    }
    
    To = sq + 17;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num] = AddTo(To) | AddFrom(sq);
            move[num] |= AddPro(1);
            num++;
        }
    }
    
    To = sq - 15;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num] = AddTo(To) | AddFrom(sq);
            move[num] |= AddPro(1);
            num++;
        }
    }
    
    To = sq - 17;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num] = AddTo(To) | AddFrom(sq);
            move[num] |= AddPro(1);
            num++;
        }
    }
    
    return num;
}

inline int GenGoldMove_b( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq - 15;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 16;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 17;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
   
    To = sq + 16;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    return num;
}

inline int GenGoldMove_w( struct Position* pos, Board sq , Move* move )
{
     int num=0;
    
    Board To = sq + 15;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 16;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 17;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 16;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    return num;
}

inline int GenBishopMove_b( struct Position* pos, Board sq , Move* move )
{
    Board To;
    int i,num=0;
    
    for( i=1; i<10; i++ )
    {
        To = sq - 17*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else 
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + 17*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else 
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - 15*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else 
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + 15*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else 
        {
            break;
        }
    }
    
    return num;
}

inline int GenBishopMove_w( struct Position* pos, Board sq , Move* move )
{
    Board To;
    int i,num=0;
    
    for( i=1; i<10; i++ )
    {
        To = sq + 17*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - 17*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + 15*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - 15*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else
        {
            break;
        }
    }
    
    return num;
}

inline int GenRookMove_b( struct Position* pos, Board sq , Move* move )
{
    Board To;
    int i,num=0;
    
    for( i=1; i<10; i++ )
    {
        To = sq - (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else 
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else 
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else 
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To<0x40 || sq<0x40 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else 
        {
            break;
        }
    }
    
    return num;
}

inline int GenRookMove_w( struct Position* pos, Board sq , Move* move )
{
    Board To;
    int i,num=0;
    
    for( i=1; i<10; i++ )
    {
        To = sq + (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
            break;
        }
        else
        {
            break;
        }
    }
    
    return num;
}

inline int GenHorseMove_b( struct Position* pos, Board sq , Move* move )
{
    int i,num=0;
    
    Board To = sq - 16;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 16;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - 17*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            break;
        }
        else 
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + 17*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            break;
        }
        else 
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - 15*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            break;
        }
        else 
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + 15*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            break;
        }
        else 
        {
            break;
        }
    }
    
    return num;
}

inline int GenHorseMove_w( struct Position* pos, Board sq , Move* move )
{
    int i,num=0;
    
    Board To = sq + 16;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 16;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + 17*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            break;
        }
        else
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - 17*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            break;
        }
        else
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + 15*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            break;
        }
        else
        {
            break;
        }
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - 15*i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
            break;
        }
        else
        {
            break;
        }
    }
    
    return num;
}

inline int GenKingMove_b( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq - 15;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 16;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 17;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 15;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 16;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 17;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    return num;
}

inline int GenKingMove_w( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq - 15;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 16;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 17;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 15;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 16;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    To = sq + 17;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    
    return num;
}

int GenMoves( struct Position* pos, Move* move)
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
                    moveNum += GenLanceMove_b( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case SKE:
                    moveNum += GenKnightMove_b( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case SGI:
                    moveNum += GenSilverMove_b( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case SKI: case STO: case SNY: case SNE: case SNG:
                    moveNum += GenGoldMove_b( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case SOU:
                    moveNum += GenKingMove_b( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case SKA:
                    moveNum += GenBishopMove_b( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case SHI:
                    moveNum += GenRookMove_b( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case SUM:
                    moveNum += GenHorseMove_b( pos, pos->piecePos[i] ,&move[moveNum] );
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
                    moveNum += GenPawnMove_w( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case EKY:
                    moveNum += GenLanceMove_w( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case EKE:
                    moveNum += GenKnightMove_w( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case EGI:
                    moveNum += GenSilverMove_w( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case EKI: case ETO: case ENY: case ENE: case ENG:
                    moveNum += GenGoldMove_w( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case EOU:
                    moveNum += GenKingMove_w( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case EKA:
                    moveNum += GenBishopMove_w( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case EHI:
                    moveNum += GenRookMove_w( pos, pos->piecePos[i] ,&move[moveNum] );
                    break;
                    case EUM:
                    moveNum += GenHorseMove_w( pos, pos->piecePos[i] ,&move[moveNum] );
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