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
jmp_buf env;

Move best;
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
			stop_search=1;
			longjmp(env, 0);
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
			stop_search=1;
			longjmp(env, 0);
		}
	}
	
	nodes++;
	
	if( depth<=0 ){
		return qsearchOld( pos, alpha, beta, 11 );
	}
	
	int standpat = evaluate( pos );
	int in_check=is_in_check( pos );

	if( !in_check ){	
		
	    if( depth < 2  ){
			
	    	if( beta + 200 <= standpat )
			{
				return beta;
			}
		} else if ( depth < 3 ) {
			
			int bound=beta + 416;
			
			int v = qsearchOld( pos, bound-1, bound, 7 );
			if( bound <= v )
			{
				return beta;
			}
		}
	    //=====================================================================
        
    }
    
	unsigned int move[768];
	int move_num=0x00;
	
	move_num += GenMoves( pos, &move[move_num] );	
	
	//====== first search ===================
	int val,max,max_i;
	int moveCount;
	
	doMove( pos, move[0] );
	if( is_in_check( pos ) ) { max=val=-INFINITE; }
	else 
    { 
        pos->color = 1 - pos->color;
        max=val=-searchOld( pos, -beta, -alpha, depth-1 ); 
    } 
	undoMove( pos, move[0] );

	if( beta <= val )
    {
		max_i=0;
		goto ADD_HASH;
	}
	if( alpha < val )
    {
		alpha=val;
	}
	//=======================================
	//===== All search ======================
	for( i=1; i<move_num; i++ ){
		
		doMove( pos, move[i] );
		if( is_in_check(pos) ) { val=-INFINITE; }
		else 
        {
            pos->color = 1 - pos->color;
            val=-searchOld( pos, -alpha-1, -alpha, depth-1 ); 
        }//NullWindow
		undoMove( pos, move[i] );
		
		if(beta <= val)
        {
			max_i=i;
			max=val;
			goto ADD_HASH;
		}
		if(alpha < val)
        {
			alpha=val;
			doMove( pos, move[i] );
			if( is_in_check(pos) ) { val=-INFINITE; }
			else
            { 
                pos->color = 1 - pos->color;
                val=-searchOld( pos, -beta, -alpha, depth-1 ); 
            }
			undoMove( pos, move[i] );
			
			if(beta <= val)
            {
				max_i=i;
				max=val;
				goto ADD_HASH;
			}
			if(alpha < val)
            {
				best=move[i];
				alpha=val;
			}
		}
		if(max < val) max=val; 
	}
	
	max_i=i-1;
	
ADD_HASH:
	
	return max;
}

void init_searchOld(){
	
	nodes=0;
	stop_search=0;
	start=timeGetTime();
	
	//if(AllTime>550000) MaxTime=8000;
	//else MaxTime=9800;
	MaxTime=15000;
}

void iterationOld( struct Position *pos )
{
    int depth,val;
	int alpha,beta;
	int i;
	
	depth=1;
	
	init_searchOld();
	
	setjmp(env);
	
	if(stop_search){
		send_best_to_usi(best);
		return;
	}
	
	while(1){
		
		alpha=-INFINITE;
		beta=INFINITE;
		//is_RootNode=true;
		
		val=searchOld( pos, alpha, beta, depth );
		if(val==INFINITE)
        { 
            //send_pv_to_usi(pv,val,depth,nodes);
            send_best_to_usi(best); 
            return; 
        }
		else if(val==-INFINITE){ printf("bestmove resign\n"); return; }
		depth++;
	}
}