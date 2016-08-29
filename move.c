#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "define.h"

void doMove( struct Position* pos, Move move )
{
    Board From = GetFrom( move );
    Board To = GetTo( move );
    Board Pro = GetPro( move );
    Piece Cap = GetCap( move );

    if( GetDrop( move ) )
    {
        pos->board[To] = From;
        //==== add
        pos->hashkey += zobrist[From][To];

        switch( pos->color )
        {
            case Black:
            if( From == SFU ) pos->Is2FU_b^=Add2FU(To%16);
            pos->boardCol_b[To] = 1;
            pos->piecePos[ pos->pieceStock[ From ][ pos->pieceStock[From][0] ] ] = To;
            pos->boardNum[To] = pos->pieceStock[ From ][ pos->pieceStock[From][0] ];
            pos->pieceStock[From][ pos->pieceStock[From][0] ] = 0;
            pos->pieceStock[From][0] -= 1;
            pos->b_hand[From] -= 1;
            pos->b_hand[0] -= 1;
            //===== sub
            pos->hashkey  -= zobHand[Black][From];
            break;
            
            case White:
            if( From == EFU ) pos->Is2FU_w^=Add2FU(To%16);
            From -= 15;
            pos->boardCol_w[To] = 1;
            pos->piecePos[ pos->pieceStock[ From ][ pos->pieceStock[From][0] ] ] = To;
            pos->boardNum[To] = pos->pieceStock[ From ][ pos->pieceStock[From][0] ];
            pos->pieceStock[From][ pos->pieceStock[From][0] ] = 0;
            pos->pieceStock[From][0] -= 1;
            pos->w_hand[From] -= 1;
            pos->w_hand[0] -= 1;
            //===== sub
            pos->hashkey  -= zobHand[White][From];
            break;
        }
    }
    else
    {
        switch( pos->color )
        {
            case Black:
            pos->boardCol_b[From] = 0;
            pos->boardCol_b[ To ] = 1;
            if( Cap )
            {
                //=== sub
                pos->hashkey -= zobrist[ pos->board[ To ] ][ To ];
                pos->boardCol_w[ To ] = 0;
                if( Cap == EFU ) pos->Is2FU_w^=Add2FU(To%16);
                if( ETO<=Cap ) { Cap-=23; }
                else{ Cap-=15; }
                pos->pieceStock[Cap][0]++; 
                pos->pieceStock[Cap][pos->pieceStock[Cap][0]] = pos->boardNum[To];
                pos->piecePos[ pos->boardNum[To] ] = 0;
                pos->b_hand[Cap]++;
                pos->b_hand[0]++;
                //==== add
                pos->hashkey  += zobHand[Black][Cap];
            }
            if( pos->board[From] == SFU && Pro ) pos->Is2FU_b^=Add2FU(To%16);
            break;
            
            case White:
            pos->boardCol_w[From] = 0;
            pos->boardCol_w[ To ] = 1;
            if( Cap )
            {
                //=== sub
                pos->hashkey -= zobrist[ pos->board[ To ] ][ To ];
                pos->boardCol_b[ To ] = 0;
                if( Cap == SFU ) pos->Is2FU_b^=Add2FU(To%16);
                if( STO<=Cap ) { Cap-=8; }
                pos->pieceStock[Cap][0]++; 
                pos->pieceStock[Cap][pos->pieceStock[Cap][0]] = pos->boardNum[To];
                pos->piecePos[ pos->boardNum[To] ] = 0;
                pos->w_hand[Cap]++;
                pos->w_hand[0]++;
                //==== add
                pos->hashkey  += zobHand[White][Cap];
            }
            if( pos->board[From] == EFU && Pro ) pos->Is2FU_w^=Add2FU(To%16);
            break;
        }
        //=== sub
        pos->hashkey -= zobrist[ pos->board[From] ][From];

        pos->board[ To ] = pos->board[From];
        if( Pro ) { pos->board[To] += 8; }
        
        //=== add 
        pos->hashkey += zobrist[ pos->board[ To ] ][ To ];

        pos->piecePos[ pos->boardNum[From] ] = To;
        pos->boardNum[ To ] = pos->boardNum[From];
        pos->boardNum[From] = 0;
        pos->board[From] = EMP;
    }
}

void undoMove( struct Position* pos, Move move )
{
    Board From = GetFrom( move );
    Board To = GetTo( move );
    Board Pro = GetPro( move );
    Piece Cap = GetCap( move );
    

    if( GetDrop( move ) )
    {
        //== sub
        pos->hashkey -= zobrist[From][To];

        pos->board[ To ] = EMP;
        
        switch( pos->color )
        {
            case Black:
            if( From == SFU ) pos->Is2FU_b^=Add2FU(To%16);
            pos->boardCol_b[To] = 0;
            pos->pieceStock[From][0] += 1;
            pos->b_hand[From] += 1;
            pos->b_hand[0] += 1;
            pos->pieceStock[From][ pos->pieceStock[From][0] ] = pos->boardNum[To];
            pos->boardNum[To] = 0;
            pos->piecePos[ pos->pieceStock[ From ][ pos->pieceStock[From][0] ] ] = 0;
            //===== add
            pos->hashkey += zobHand[Black][From];
            break;
            
            case White:
            if( From == EFU ) pos->Is2FU_w^=Add2FU(To%16);
            From -= 15;
            pos->boardCol_w[To] = 0;
            pos->pieceStock[From][0] += 1;
            pos->w_hand[From] += 1;
            pos->w_hand[0] += 1;
            pos->pieceStock[From][ pos->pieceStock[From][0] ] = pos->boardNum[To];
            pos->boardNum[To] = 0;
            pos->piecePos[ pos->pieceStock[ From ][ pos->pieceStock[From][0] ] ] = 0;
            //===== add
            pos->hashkey  += zobHand[White][From];
            break;
        }
    }
    else
    {
        //=== sub
        pos->hashkey -= zobrist[pos->board[To]][To];

        if( Pro )
        {
            pos->board[From] = pos->board[ To ] - 8;
        }
        else
        {
            pos->board[From] = pos->board[ To ];
        }
        //=== add
        pos->hashkey += zobrist[ pos->board[ From ] ][ From ];
        
        pos->boardNum[From] = pos->boardNum[ To ];
        pos->boardNum[ To ] = 0;
        pos->piecePos[ pos->boardNum[From] ] = From;
        pos->board[ To ] = Cap;
         
        switch( pos->color )
        {
            case Black:
            pos->boardCol_b[From] = 1;
            pos->boardCol_b[ To ] = 0;
            if( Cap )
            { 
                //=== add
                pos->hashkey += zobrist[ Cap ][ To ];

                pos->boardCol_w[ To ] = 1;
                if( Cap == EFU ) pos->Is2FU_w^=Add2FU(To%16);
                if( ETO<=Cap ) { Cap-=23; }
                else{ Cap-=15; }
                pos->b_hand[Cap]--;
                pos->b_hand[0] -= 1;
                pos->boardNum[To] = pos->pieceStock[Cap][pos->pieceStock[Cap][0]];
                pos->piecePos[ pos->boardNum[To] ] = To;
                pos->pieceStock[Cap][pos->pieceStock[Cap][0]] = 0;
                pos->pieceStock[Cap][0]--;
                //=== sub
                pos->hashkey  -= zobHand[Black][Cap];
            }
            if(pos->board[From] == SFU && Pro ) pos->Is2FU_b^=Add2FU(To%16);
            break;
            
            case White:
            pos->boardCol_w[From] = 1;
            pos->boardCol_w[ To ] = 0;
            if( Cap )
            { 
                //=== add
                pos->hashkey += zobrist[ Cap ][ To ];
                
                pos->boardCol_b[ To ] = 1;
                if( Cap == SFU ) pos->Is2FU_b^=Add2FU(To%16);
                if( STO<=Cap ) { Cap-=8; }
                pos->w_hand[Cap]--;
                pos->w_hand[0] -= 1;
                pos->boardNum[To] = pos->pieceStock[Cap][pos->pieceStock[Cap][0]];
                pos->piecePos[ pos->boardNum[To] ] = To;
                pos->pieceStock[Cap][pos->pieceStock[Cap][0]] = 0;
                pos->pieceStock[Cap][0]--;   
                //==== sub
                pos->hashkey  -= zobHand[White][Cap];
            }
            if( pos->board[From] == EFU && Pro ) pos->Is2FU_w^=Add2FU(To%16);
            break;
        }
    }
}