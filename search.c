#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <setjmp.h>
#include <time.h>

#include "define.h"
#include "math.h"
#include "score.h"
#include "tt.h"
#include "search.h"

jmp_buf env;

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
/* Novice_DenouT4_final の探索 */
Score search( struct Position *pos, Score alpha, Score beta, const Depth depth )
{
    
}

/* Novice_wcsc26_final の探索 */

uint64 MaxTime;
uint64 start;
uint64 nodes;
Move pv[32][32];

int stop_search;

void swap(unsigned int *a,unsigned int *b){
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

int qsearchOld( struct Position *pos, Score alpha, Score beta, const Depth depth ){
	
	if(nodes%16384==0)
    {
		int current=timeGetTime();
		int usi_time=current-start;
		if(usi_time>0 && nodes%1638400==0)
        {
			printf("info nps %lld\n",(nodes/usi_time)*1000);
		}
		//if( IsStopReceived ){ stop_search=1; longjmp(env, 0); }
		if( usi_time>=MaxTime ){
			return -INFINITE+3;
		}
	}
	
	int standpat = evaluate(pos);
	int i,j,val;
	unsigned int Val[768];
	int max,maxid;
	nodes++;
	
	if( depth<=0 ){
		return standpat;
	}
	
	if(standpat > alpha){
		if(standpat >= beta){
			return standpat;
		}
		alpha=standpat;
	}
	//======= Futility Pruning ============================================	
	if( beta+300<=standpat ) return beta;
	//=====================================================================
	unsigned int move[768];
	int move_num=0x00;
	move_num+=GenMoves( pos, &move[move_num] );
    
	for(i=0;i<move_num;i++){
		Val[i]=GetCap(move[i])*( 31 - pos->board[ GetFrom(move[i]) ]);
	}
	
	for(i=0;i<move_num-1;i++){
		max=Val[i];
		maxid=i;
		for(j=i+1;j<move_num;j++){
			if(Val[j]>max){
				max=Val[j];
				maxid=j;
			}
		}
		swap(&Val[i],&Val[maxid]);
		swap(&move[i],&move[maxid]);
	}
	
	for(i=0;i<move_num;i++){
		if(!GetCap(move[i])) continue;
		doMove( pos, move[i] );
		if(is_in_check( pos )) { val=-INFINITE; }
		else 
        {
            pos->color = 1 - pos->color;
            val=-qsearchOld( pos, -beta, -alpha, depth-1 ); 
            pos->color = 1 - pos->color; 
        }
		undoMove( pos, move[i] );
		if(beta <= val){
			return val;
		}
		if(alpha < val){
			alpha=val;
		}
	}
	return alpha;
}

Score searchOld( struct Position *pos, Score alpha, Score beta, const Depth depth )
{
    int i,j,k;
	Depth newDepth;
	Depth extension;
	Score bestScore;
	Score score;
	Move bestMove;
	bool doFullDepthSearch;
	bool isPVMove;
	int  moveCount;

	moveCount = 0;

	if(nodes%16384==0)
    {
		int current=timeGetTime();
		int usi_time=current-start;
		if(usi_time>0 && nodes%1638400==0)
        {
			printf("info nps %lld\n",(nodes/usi_time)*1000);
		}
		//if( IsStopReceived ){ stop_search=1; longjmp(env, 0); }
		if( usi_time>=MaxTime ){
			return -INFINITE+3;
		}
	}
	
	if( depth<=0 ){
		return qsearchOld( pos, alpha, beta, 11 );
	}

	nodes++;
	
	bestScore = -INFINITE;
    
	Move move[768];
	int move_num=0x00;
	
	move_num += GenMoves( pos, &move[move_num] );	

	//===== All search ======================
	for( i=0; i<move_num; i++ )
	{	
		doMove( pos, move[i] );
		if( is_in_check(pos) ) 
		{ 
			undoMove( pos, move[i] );
			continue; 
		}

		moveCount++;

		if( moveCount == 1 ) isPVMove = true;
		else isPVMove = false;

		doFullDepthSearch = !isPVMove;
		
		// step16
		//full depth search (PVS)
		if( doFullDepthSearch )
		{
			pos->color = 1 - pos->color;
			score = -searchOld( pos, -(alpha+1), -alpha, depth-1 ); 
			pos->color = 1 - pos->color;
		}
		
		if( isPVMove || ( alpha<score && score<beta ) )
		{
			pos->color = 1 - pos->color;
			score = -searchOld( pos, -beta, -alpha, depth-1 ); 
			pos->color = 1 - pos->color;
		}

		// step17
		undoMove( pos, move[i] );
	
		// step18
		if( bestScore < score )
		{
			bestScore = score;

			if( alpha < score )
			{
				bestMove = move[i];
				pv[depth][depth] = bestMove;
				for(j=depth-1;j>0;j--) {
					pv[depth][j]=pv[depth-1][j];
				}

				if( score < beta )
				{
					alpha = score;
				}
				else {
					// fail high
					break;
				}
			}
		}
	}

	// step20
	if( moveCount == 0 ) return -INFINITE;

	if( bestScore == -INFINITE )
	{
		bestScore = alpha;
	}

	if( beta <= bestScore )
	{
		//todo add killer and hash
	}

	return bestScore;
}

void init_searchOld(){
	
    int i,j;

	nodes=0;
	stop_search=0;
	start=timeGetTime();
	for( i=0; i<32; i++ ){
		for( j=0; j<32; j++ ){
			pv[i][j]=0;
		}
	}
	//if(AllTime>550000) MaxTime=8000;
	//else MaxTime=9800;
	MaxTime=3000;
}

void iterationOld( struct Position *pos )
{
    int depth,val;
	int alpha,beta;
	int i;
	
	Move best;

	depth=1;
	
	init_searchOld();

	while(1)
	{	
		alpha=-INFINITE;
		beta=INFINITE;
		//is_RootNode=true;
		
		val=searchOld( pos, alpha, beta, depth );
		if( val == -INFINITE + 3 || val == INFINITE - 3 )
		{
			send_best_to_usi(best);
			return;
		}
		else if(val==INFINITE)
        { 
            //send_pv_to_usi(pv,val,depth,nodes);
            send_best_to_usi(pv[depth][depth]); 
            return; 
        }
		else if(val==-INFINITE){ printf("bestmove resign\n"); return; }
		
		send_pv_to_usi( pos, pv, val, depth, nodes );
		//printf("move:%d\n",pv[depth][depth]);
        best = pv[depth][depth];
		depth++;
	}
}

