#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "search.h"
#include "score.h"
#include "tt.h"


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

    INCHECK = isInCheck( pos );

    evaluate( pos, ss );

    move[600];
    int num = GenMoves( pos, &move[0] );
    
    //todo:ここでオーダリング 

    int i;
    for( i=0, i<num; i++ )
    {
        //todo:取る手だけ残す
        givesCheck = moveGiveCheck( pos );

        if (!ss->PVNode
			&& !INCHECK // 駒打ちは王手回避のみなので、ここで弾かれる。
			&& !givesCheck
			/*&& move != ttMove*/)
		{
			futilityScore =
				futilityBase + Position::capturePieceScore(pos.piece(move.to()));
			if (move.isPromotion())
				futilityScore += Position::promotePieceScore(move.pieceTypeFrom());

			if (futilityScore < beta) {
				bestScore = std::max(bestScore, futilityScore);
				continue;
			}
        }

    }
}

Score search(struct Position *pos, Score alpha, Score beta, const Depth depth )
{

}