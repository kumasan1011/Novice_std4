#ifndef _GENMOVE_H_
#define _GENMOVE_H_

int GenPawnMove_b( struct Position*, int, Move* );
int GenLanceMove_b( struct Position*, int, Move* );
int GenKnightMove_b( struct Position*, int, Move* );
int GenSilverMove_b( struct Position*, int, Move* );
int GenGoldMove_b( struct Position*, int, Move* );
int GenKingMove_b( struct Position*, int, Move* );
int GenBishopMove_b( struct Position*, int, Move* );
int GenRookMove_b( struct Position*, int, Move* );
int GenHorseMove_b( struct Position*, int, Move* );
int GenDragonMove_b( struct Position*, int, Move* );

int GenPawnMove_w( struct Position*, int, Move* );
int GenLanceMove_w( struct Position*, int, Move* );
int GenKnightMove_w( struct Position*, int, Move* );
int GenSilverMove_w( struct Position*, int, Move* );
int GenGoldMove_w( struct Position*, int, Move* );
int GenKingMove_w( struct Position*, int, Move* );
int GenBishopMove_w( struct Position*, int, Move* );
int GenRookMove_w( struct Position*, int, Move* );
int GenHorseMove_w( struct Position*, int, Move* );
int GenDragonMove_w( struct Position*, int, Move* );


#endif //_GENMOVE_H_