#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "define.h"
#include "score.h"
#include "tt.h"
#include "search.h"


Score qsearch( struct Position *pos, struct SearchStack *ss, Score alpha, Score beta, const Depth depth )
{
    /* とりあえずAperyに合わせる */
    Move ttMove;
    Move move;
    Move bestMove;
    Score bestScore;
    Score score;
    Score ttScore;
    Score futilityScore;
    Score futilityBase;
    Score oldAlpha;
    bool giveCheck;
    bool ttHit;
    bool INCHECK;
    /**************************/

    /*
    INCHECK = isInCheck( pos );

    evaluate( pos, ss );

    move[600];
    int num = GenMoves( pos, &move[0] );
    
    //todo:ここでオーダリング 

    int i;
    for( i=0, i<num; i++ )
    {
        if( !GetCap(move[i]) ) continue; 
        givesCheck = moveGiveCheck( pos );

    }*/
}

Score search(struct Position *pos, Score alpha, Score beta, const Depth depth )
{
    
}