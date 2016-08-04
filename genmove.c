#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
        if( pos->board[To] )
        {
            move[0] |= AddCap( pos->board[To] );
        }
        return 1;
    }
    
    return 0;
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
        if( pos->board[To] )
        {
            move[0] |= AddCap( pos->board[To] );
        }
        return 1;
    }
    
    return 0;
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
            move[num++] = AddTo(To) | AddFrom(sq);
            
            if( To<0x40 || sq<0x40 ) //成り
            {
                if( To<0x30 )
                {
                    move[num-1] |= AddPro(1);
                }
                else
                {
                    move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
                }
            }
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
            if( To<0x40 || sq<0x40 ) //成り
            {
                if( To<0x30 )
                {
                    move[num-1] |= AddPro(1);
                }
                else
                {
                    move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
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
            move[num++] = AddTo(To) | AddFrom(sq);

            if( To>0x70 || sq>0x70 ) //成り
            {
                if( To>0x80 )
                {
                    move[num-1] |= AddPro(1);
                }
                else
                {
                    move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
                }
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );

            if( To>0x70 || sq>0x70 ) //成り
            {
                if( To>0x80 )
                {
                    move[num-1] |= AddPro(1);
                }
                else
                {
                    move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
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
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);

        if( To<0x40 || sq<0x40 ) //成り
        {
            if( To<0x30 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
            }
        }
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );

        if( To<0x40 || sq<0x40 ) //成り
        {
            if( To<0x30 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
            }
        }
    }
    
    To = sq - 33;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);

        if( To<0x40 || sq<0x40 ) //成り
        {
            if( To<0x30 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
            }
        }
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );

        if( To<0x40 || sq<0x40 ) //成り
        {
            if( To<0x30 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
            }
        }
    }
    
    return num;
}

inline int GenKnightMove_w( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq + 31;
    
    if( !pos->board[To])
    {
        move[num++] = AddTo(To) | AddFrom(sq);

        if( To>0x70 || sq>0x70 ) //成り
        {
            if( To>0x80 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
            }
        }
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );

        if( To>0x70 || sq>0x70 ) //成り
        {
            if( To>0x80 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
            }
        }
    }
    
    To = sq + 33;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);

        if( To>0x70 || sq>0x70 ) //成り
        {
            if( To>0x80 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
            }
        }
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );

        if( To>0x70 || sq>0x70 ) //成り
        {
            if( To>0x80 )
            {
                move[num-1] |= AddPro(1);
            }
            else
            {
                move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
            }
        }
    }

    return num;
}

inline int GenSilverMove_b( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq - 15;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);

        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    To = sq - 16;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    To = sq - 17;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    To = sq + 15;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    To = sq + 17;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        if( To<0x40 || sq<0x40 ) //成り
        {
             move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    return num;
}

inline int GenSilverMove_w( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq + 15;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    To = sq + 16;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    To = sq + 17;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    To = sq - 15;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    To = sq - 17;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1);
        }
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        
        if( To>0x70 || sq>0x70 ) //成り
        {
            move[num++] = AddTo(To) | AddFrom(sq) | AddPro(1) | AddCap( pos->board[To] );
        }
    }
    
    return num;
}

inline int GenGoldMove_b( struct Position* pos, Board sq , Move* move )
{
    int num=0;
    
    Board To = sq - 15;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }
    
    To = sq - 16;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }

    To = sq - 17;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }
    
    To = sq - 1;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }
    
    To = sq + 1;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }
   
    To = sq + 16;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_w[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }
    
    return num;
}

inline int GenGoldMove_w( struct Position* pos, Board sq , Move* move )
{
     int num=0;
    
    Board To = sq + 15;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }

    To = sq + 16;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }
    
    To = sq + 17;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }
    
    To = sq + 1;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }
    
    To = sq - 1;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
    }
    
    To = sq - 16;
    
    if( !pos->board[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq);
    }
    else if( pos->boardCol_b[To] )
    {
        move[num++] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
        if( pos->board[To]==EMP )
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] ); 
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) ;
            num++;
            if( To>0x70 || sq>0x70 ) //成り
            {
                move[num-1] |= AddPro(1);
            }
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 16;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 16;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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

inline int GenDragonMove_b( struct Position* pos, Board sq , Move* move )
{
    int i,num=0;
    
    Board To = sq - 15;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 15;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 17;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 17;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq - (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
        To = sq + (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
        To = sq - i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
        To = sq + i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_w[To] )
        {
            
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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

inline int GenDragonMove_w( struct Position* pos, Board sq , Move* move )
{
    int i,num=0;
    
    Board To = sq + 15;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 15;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 17;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 17;
    
    if( !pos->board[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq);
        num++;
    }
    else if( pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    for( i=1; i<10; i++ )
    {
        To = sq + (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
        To = sq - (i<<4);
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
        To = sq + i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
        To = sq - i;
        if( !pos->board[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq);
            num++;
        }
        else if( pos->boardCol_b[To] )
        {
            move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 16;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 17;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 15;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 16;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 17;
    
    if( !pos->board[To] || pos->boardCol_w[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
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
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 16;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 17;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq - 1;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 1;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 15;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 16;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    To = sq + 17;
    
    if( !pos->board[To] || pos->boardCol_b[To] )
    {
        move[num] = AddTo(To) | AddFrom(sq) | AddCap( pos->board[To] );
        num++;
    }
    
    return num;
}

inline int GenDropMoves_b( struct Position* pos, Board To, Move* move ) //制限なし
{
    int num=0;
    
    if( pos->b_hand[FU] && !(( pos->Is2FU_b >> (10-To%16 )) & 0x01 )  )
    {
        move[num++] = AddTo(To) | AddFrom(SFU) | AddDrop(1);
    }
    if( pos->b_hand[KY] )
    {
        move[num++] = AddTo(To) | AddFrom(SKY) | AddDrop(1);
    }
    if( pos->b_hand[KE] )
    {
        move[num++] = AddTo(To) | AddFrom(SKE) | AddDrop(1);
    }
    if( pos->b_hand[GI] )
    {
        move[num++] = AddTo(To) | AddFrom(SGI) | AddDrop(1);
    }
    if( pos->b_hand[KI] )
    {
        move[num++] = AddTo(To) | AddFrom(SKI) | AddDrop(1);
    }
    if( pos->b_hand[KA] )
    {
        move[num++] = AddTo(To) | AddFrom(SKA) | AddDrop(1);
    }
    if( pos->b_hand[HI] )
    {
        move[num++] = AddTo(To) | AddFrom(SHI) | AddDrop(1);
    }
    
    return num;
}

inline int GenDropMoves_b_rank1( struct Position* pos, Board To, Move* move ) //1段目
{
    int num=0;
    
    if( pos->b_hand[GI] )
    {
        move[num++] = AddTo(To) | AddFrom(SGI) | AddDrop(1);
    }
    if( pos->b_hand[KI] )
    {
        move[num++] = AddTo(To) | AddFrom(SKI) | AddDrop(1);
    }
    if( pos->b_hand[KA] )
    {
        move[num++] = AddTo(To) | AddFrom(SKA) | AddDrop(1);
    }
    if( pos->b_hand[HI] )
    {
        move[num++] = AddTo(To) | AddFrom(SHI) | AddDrop(1);
    }
    
    return num;
}

inline int GenDropMoves_b_rank2( struct Position* pos, Board To, Move* move ) //2段目
{
    int num=0;
    
    if( pos->b_hand[FU] && !(( pos->Is2FU_b >> (10-To%16 )) & 0x01 ) )
    {
        move[num++] = AddTo(To) | AddFrom(SFU) | AddDrop(1);
    }
    if( pos->b_hand[KY] )
    {
        move[num++] = AddTo(To) | AddFrom(SKY) | AddDrop(1);
    }
    if( pos->b_hand[GI] )
    {
        move[num++] = AddTo(To) | AddFrom(SGI) | AddDrop(1);
    }
    if( pos->b_hand[KI] )
    {
        move[num++] = AddTo(To) | AddFrom(SKI) | AddDrop(1);
    }
    if( pos->b_hand[KA] )
    {
        move[num++] = AddTo(To) | AddFrom(SKA) | AddDrop(1);
    }
    if( pos->b_hand[HI] )
    {
        move[num++] = AddTo(To) | AddFrom(SHI) | AddDrop(1);
    }
    
    return num;
}

inline int GenDropMoves_w( struct Position* pos, Board To, Move* move ) //制限なし
{
    int num=0;
    
    if( pos->w_hand[FU] && !(( pos->Is2FU_w >> (10-To%16 )) & 0x01 ) )
    {
        move[num++] = AddTo(To) | AddFrom(EFU) | AddDrop(1);
    }
    if( pos->w_hand[KY] )
    {
        move[num++] = AddTo(To) | AddFrom(EKY) | AddDrop(1);
    }
    if( pos->w_hand[KE] )
    {
        move[num++] = AddTo(To) | AddFrom(EKE) | AddDrop(1);
    }
    if( pos->w_hand[GI] )
    {
        move[num++] = AddTo(To) | AddFrom(EGI) | AddDrop(1);
    }
    if( pos->w_hand[KI] )
    {
        move[num++] = AddTo(To) | AddFrom(EKI) | AddDrop(1);
    }
    if( pos->w_hand[KA] )
    {
        move[num++] = AddTo(To) | AddFrom(EKA) | AddDrop(1);
    }
    if( pos->w_hand[HI] )
    {
        move[num++] = AddTo(To) | AddFrom(EHI) | AddDrop(1);
    }
    
    return num;
}

inline int GenDropMoves_w_rank8( struct Position* pos, Board To, Move* move ) //8段目
{
    int num=0;
    
    if( pos->w_hand[FU] && !(( pos->Is2FU_w >> (10-To%16 )) & 0x01 ))
    {
        move[num++] = AddTo(To) | AddFrom(EFU) | AddDrop(1);
    }
    if( pos->w_hand[KY] )
    {
        move[num++] = AddTo(To) | AddFrom(EKY) | AddDrop(1);
    }
    if( pos->w_hand[GI] )
    {
        move[num++] = AddTo(To) | AddFrom(EGI) | AddDrop(1);
    }
    if( pos->w_hand[KI] )
    {
        move[num++] = AddTo(To) | AddFrom(EKI) | AddDrop(1);
    }
    if( pos->w_hand[KA] )
    {
        move[num++] = AddTo(To) | AddFrom(EKA) | AddDrop(1);
    }
    if( pos->w_hand[HI] )
    {
        move[num++] = AddTo(To) | AddFrom(EHI) | AddDrop(1);
    }
    
    return num;
}

inline int GenDropMoves_w_rank9( struct Position* pos, Board To, Move* move ) //9段目
{
    int num=0;
   
    if( pos->w_hand[GI] )
    {
        move[num++] = AddTo(To) | AddFrom(EGI) | AddDrop(1);
    }
    if( pos->w_hand[KI] )
    {
        move[num++] = AddTo(To) | AddFrom(EKI) | AddDrop(1);
    }
    if( pos->w_hand[KA] )
    {
        move[num++] = AddTo(To) | AddFrom(EKA) | AddDrop(1);
    }
    if( pos->w_hand[HI] )
    {
        move[num++] = AddTo(To) | AddFrom(EHI) | AddDrop(1);
    }
    
    return num;
}

int GenMoves( struct Position* pos, Move* move )
{
    int i,x,y,sq;
    int moveNum = 0;
    
    switch( pos->color )
    {
        case Black:
        if( pos->b_hand[0] )
        {
            for( sq=0x11; sq<=0x19; sq++ )//１段目
            {
                if( !pos->board[sq] ) //空き升
                {
                    moveNum += GenDropMoves_b_rank1( pos, sq, &move[moveNum] );
                }
                else 
                {
                    switch( pos->board[ sq ] )
                    {
                        case SFU:
                        moveNum += GenPawnMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKY:
                        moveNum += GenLanceMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKE:
                        moveNum += GenKnightMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SGI:
                        moveNum += GenSilverMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKI: case STO: case SNY: case SNE: case SNG:
                        moveNum += GenGoldMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SOU:
                        moveNum += GenKingMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKA:
                        moveNum += GenBishopMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SHI:
                        moveNum += GenRookMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SUM:
                        moveNum += GenHorseMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SRY:
                        moveNum += GenDragonMove_b( pos, sq, &move[moveNum] );
                        break;
                        default:
                        continue;
                    }
                }
            }
            
            for( sq=0x21; sq<=0x29; sq++ )//2段目
            {
                if( !pos->board[sq] ) //空き升
                {
                    moveNum += GenDropMoves_b_rank2( pos, sq, &move[moveNum] );
                }
                else
                {
                    switch( pos->board[ sq ] )
                    {
                        case SFU:
                        moveNum += GenPawnMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKY:
                        moveNum += GenLanceMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKE:
                        moveNum += GenKnightMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SGI:
                        moveNum += GenSilverMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKI: case STO: case SNY: case SNE: case SNG:
                        moveNum += GenGoldMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SOU:
                        moveNum += GenKingMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKA:
                        moveNum += GenBishopMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SHI:
                        moveNum += GenRookMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SUM:
                        moveNum += GenHorseMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SRY:
                        moveNum += GenDragonMove_b( pos, sq, &move[moveNum] );
                        break;
                        default:
                        continue;
                    }
                }
            }
            
            for( y=0x30; y<=0x90; y+=0x10 )
            {
                for( x=0x01; x<=0x09; x++ )
                {
                    sq = y + x;
                    if( !pos->board[sq] ) //空き升
                    {
                        moveNum += GenDropMoves_b( pos, sq, &move[moveNum] );
                    }
                    else
                    {
                        switch( pos->board[ sq ] )
                        {
                            case SFU:
                            moveNum += GenPawnMove_b( pos, sq, &move[moveNum] );
                            break;
                            case SKY:
                            moveNum += GenLanceMove_b( pos, sq, &move[moveNum] );
                            break;
                            case SKE:
                            moveNum += GenKnightMove_b( pos, sq, &move[moveNum] );
                            break;
                            case SGI:
                            moveNum += GenSilverMove_b( pos, sq, &move[moveNum] );
                            break;
                            case SKI: case STO: case SNY: case SNE: case SNG:
                            moveNum += GenGoldMove_b( pos, sq, &move[moveNum] );
                            break;
                            case SOU:
                            moveNum += GenKingMove_b( pos, sq, &move[moveNum] );
                            break;
                            case SKA:
                            moveNum += GenBishopMove_b( pos, sq, &move[moveNum] );
                            break;
                            case SHI:
                            moveNum += GenRookMove_b( pos, sq, &move[moveNum] );
                            break;
                            case SUM:
                            moveNum += GenHorseMove_b( pos, sq, &move[moveNum] );
                            break;
                            case SRY:
                            moveNum += GenDragonMove_b( pos, sq, &move[moveNum] );
                            break;
                            default:
                            continue;
                        }
                    }
                }
            }
        }
        else //持ち駒を持っていない
        {
            for( y=0x10; y<=0x90; y+=0x10 )
            {
                for( x=0x01; x<=0x09; x++ )
                {
                    sq = y + x;
                    switch( pos->board[ sq ] )
                    {
                        case EMP:
                        break;
                        case SFU:
                        moveNum += GenPawnMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKY:
                        moveNum += GenLanceMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKE:
                        moveNum += GenKnightMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SGI:
                        moveNum += GenSilverMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKI: case STO: case SNY: case SNE: case SNG:
                        moveNum += GenGoldMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SOU:
                        moveNum += GenKingMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SKA:
                        moveNum += GenBishopMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SHI:
                        moveNum += GenRookMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SUM:
                        moveNum += GenHorseMove_b( pos, sq, &move[moveNum] );
                        break;
                        case SRY:
                        moveNum += GenDragonMove_b( pos, sq, &move[moveNum] );
                        break;
                        default:
                        continue;
                    }
                }
            }
        }
        
        break;
        
        //後手
        case White:
        if( pos->w_hand[0] )
        {
            for( y=0x10; y<=0x70; y+=0x10 )
            {
                for( x=0x01; x<=0x09; x++ )
                {
                    sq = y + x;
                    if( !pos->board[sq] ) //空き升
                    {
                        moveNum += GenDropMoves_w( pos, sq, &move[moveNum] );
                    }
                    else if( pos->boardCol_w[sq] )
                    {
                        switch( pos->board[ sq ] )
                        {
                            case EFU:
                            moveNum += GenPawnMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EKY:
                            moveNum += GenLanceMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EKE:
                            moveNum += GenKnightMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EGI:
                            moveNum += GenSilverMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EKI: case STO: case SNY: case SNE: case SNG:
                            moveNum += GenGoldMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EOU:
                            moveNum += GenKingMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EKA:
                            moveNum += GenBishopMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EHI:
                            moveNum += GenRookMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EUM:
                            moveNum += GenHorseMove_w( pos, sq, &move[moveNum] );
                            break;
                            case ERY:
                            moveNum += GenDragonMove_w( pos, sq, &move[moveNum] );
                            break;
                        }
                    }
                }
            }
            for( sq=0x81; sq<=0x89; sq++ )//8段目
            {
                if( !pos->board[sq] ) //空き升
                {
                    moveNum += GenDropMoves_w_rank8( pos, sq, &move[moveNum] );
                }
                else if( pos->boardCol_w[sq] )
                {
                    switch( pos->board[ sq ] )
                    {
                        case EFU:
                        moveNum += GenPawnMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EKY:
                        moveNum += GenLanceMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EKE:
                        moveNum += GenKnightMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EGI:
                        moveNum += GenSilverMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EKI: case STO: case SNY: case SNE: case SNG:
                        moveNum += GenGoldMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EOU:
                        moveNum += GenKingMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EKA:
                        moveNum += GenBishopMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EHI:
                        moveNum += GenRookMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EUM:
                        moveNum += GenHorseMove_w( pos, sq, &move[moveNum] );
                        break;
                        case ERY:
                        moveNum += GenDragonMove_w( pos, sq, &move[moveNum] );
                        break;
                    }
                }
            }
            
            for( sq=0x91; sq<=0x99; sq++ )//9段目
            {
                if( !pos->board[sq] ) //空き升
                {
                    moveNum += GenDropMoves_w_rank9( pos, sq, &move[moveNum] );
                }
                else if( pos->boardCol_w[sq] )
                {
                    switch( pos->board[ sq ] )
                    {
                        case EFU:
                        moveNum += GenPawnMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EKY:
                        moveNum += GenLanceMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EKE:
                        moveNum += GenKnightMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EGI:
                        moveNum += GenSilverMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EKI: case STO: case SNY: case SNE: case SNG:
                        moveNum += GenGoldMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EOU:
                        moveNum += GenKingMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EKA:
                        moveNum += GenBishopMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EHI:
                        moveNum += GenRookMove_w( pos, sq, &move[moveNum] );
                        break;
                        case EUM:
                        moveNum += GenHorseMove_w( pos, sq, &move[moveNum] );
                        break;
                        case ERY:
                        moveNum += GenDragonMove_w( pos, sq, &move[moveNum] );
                        break;
                    }
                }
            }
        }
        else
        {
            for( y=0x10; y<=0x90; y+=0x10 )
            {
                for( x=0x01; x<=0x09; x++ )
                {
                    sq = y + x;

                    if( pos->boardCol_w[sq] )
                    {
                        switch( pos->board[ sq ] )
                        {
                            case EFU:
                            moveNum += GenPawnMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EKY:
                            moveNum += GenLanceMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EKE:
                            moveNum += GenKnightMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EGI:
                            moveNum += GenSilverMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EKI: case STO: case SNY: case SNE: case SNG:
                            moveNum += GenGoldMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EOU:
                            moveNum += GenKingMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EKA:
                            moveNum += GenBishopMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EHI:
                            moveNum += GenRookMove_w( pos, sq, &move[moveNum] );
                            break;
                            case EUM:
                            moveNum += GenHorseMove_w( pos, sq, &move[moveNum] );
                            break;
                            case ERY:
                            moveNum += GenDragonMove_w( pos, sq, &move[moveNum] );
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
    
    return moveNum;
}

/*
int GenOnlyMoves( struct Position* pos, Move* move )
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
                    moveNum += GenPawnMove_b( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case SKY:
                    moveNum += GenLanceMove_b( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case SKE:
                    moveNum += GenKnightMove_b( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case SGI:
                    moveNum += GenSilverMove_b( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case SKI: case STO: case SNY: case SNE: case SNG:
                    moveNum += GenGoldMove_b( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case SOU:
                    moveNum += GenKingMove_b( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case SKA:
                    moveNum += GenBishopMove_b( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case SHI:
                    moveNum += GenRookMove_b( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case SUM:
                    moveNum += GenHorseMove_b( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case SRY:
                    moveNum += GenDragonMove_b( pos, pos->piecePos[i], &move[moveNum] );
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
                    moveNum += GenPawnMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case EKY:
                    moveNum += GenLanceMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case EKE:
                    moveNum += GenKnightMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case EGI:
                    moveNum += GenSilverMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case EKI: case ETO: case ENY: case ENE: case ENG:
                    moveNum += GenGoldMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case EOU:
                    moveNum += GenKingMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case EKA:
                    moveNum += GenBishopMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case EHI:
                    moveNum += GenRookMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case EUM:
                    moveNum += GenHorseMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                    case ERY:
                    moveNum += GenDragonMove_w( pos, pos->piecePos[i], &move[moveNum] );
                    break;
                }
            }
        }
        break;
    }
    return moveNum; 
}
*/