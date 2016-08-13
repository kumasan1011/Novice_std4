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

Score FutilityMargins[16][64];
Score FutilityMoveCounts[32];

/* Novice_wcsc26_final の探索 */

uint64 MaxTime;
uint64 start;
uint64 nodes;
Move pv[32][32];


void swap(unsigned int *a,unsigned int *b){
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

void moveOrder( struct Position *pos, struct SearchStack *ss, Move *move, int end_num, Depth depth )
{	
	int i,j;
	unsigned int Val[768];
	int max,maxid;
	
	for( i=0; i<end_num; i++ )
	{
		if(move[i]==pv[depth][depth]){	Val[i]=5500; continue; }
		//TODO  here is good_cap (SEE>0) move 
		if(move[i]==ss->Killers[0]){ Val[i]=100; continue; }
		if(move[i]==ss->Killers[1]){ Val[i]=50; continue; }
		
		Val[i]=GetCap(move[i])*( 31 - pos->board[GetFrom(move[i])] )*3;
		Val[i]+=rand()%20;
	}
	
	for(i=0;i<end_num-1;i++){
		max=Val[i];
		maxid=i;
		for(j=i+1;j<end_num;j++){
			if(Val[j]>max){
				max=Val[j];
				maxid=j;
			}
		}
		swap(&Val[i],&Val[maxid]);
		swap(&move[i],&move[maxid]);
	}
	
}

Score qsearch( struct Position *pos, struct SearchStack *ss, Score alpha, Score beta, const Depth depth, const bool PVNode )
{	
	int i,j,k;
	Depth newDepth;
	Depth extension;
	Score bestScore;
	Score score;
	Score oldAlpha;
	Score futilityScore;
	Score futilityBase;
	Move bestMove;
	Move move[768];
	Score Val[768];
	bool doFullDepthSearch;
	bool isPVMove;
	int  moveCount;
	int  inCheck;
	int move_num=0x00;

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
		return evaluate(pos);
	}

	nodes++;
	
	if( PVNode )
	{
		oldAlpha = alpha;
	}

	ss->currentMove = bestMove = 0;
	
	inCheck = is_in_check(pos);

	if(inCheck)
	{
		ss->staticEval = 0;
		bestScore = futilityBase = -INFINITE;
		return evaluate(pos);
	}
	else {
		ss->staticEval = bestScore = evaluate(pos);

		if( beta <= bestScore )
		{
			return bestScore;
		}
		
		if( PVNode && alpha < bestScore )
		{
			alpha = bestScore;
		}

		futilityBase = bestScore + 250; //todo: 要調整
	}

	move_num+=GenMoves( pos, &move[move_num] );
    
	for(i=0;i<move_num;i++){
		Val[i]=GetCap(move[i])*( 31 - pos->board[ GetFrom(move[i]) ]);
	}
	
	int max,maxid;
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

		if( !PVNode 
			&& !inCheck)
		{
			futilityScore = futilityBase + 300; //todo: 要調整
			
			if( futilityScore < beta )
			{
				bestScore = ((bestScore > futilityScore) ? bestScore : futilityBase );
				continue;
			}
		}

		doMove( pos, move[i] );
		if(is_in_check( pos )) 
		{ 
			undoMove( pos, move[i] );
			continue; 
		}
		else 
        {
			ss->currentMove = move[i];

            pos->color = 1 - pos->color;
            score=-qsearch( pos, ss+1, -beta, -alpha, depth-1, PVNode ); 
            pos->color = 1 - pos->color; 
        }
		undoMove( pos, move[i] );

		if( bestScore < score )
		{
			bestScore = score;

			if( alpha < score )
			{
				if( PVNode && score < beta )
				{
					alpha = score;
					bestMove = move[i];
				}
				else {
					// fail high
					return score;
				}
			}
		}
	}
	return bestScore;
}

Score search( struct Position *pos, struct SearchStack *ss, Score alpha, Score beta, const Depth depth, const bool PVNode )
{
	// goto 関連によりここで定義しとかないとErrorを吐く
    int i,j,k;
	Depth newDepth;
	Depth extension;
	struct StateInfo st;
	Score bestScore;
	Score score;
	Score eval;
	Move bestMove;
	Move move[768];
	bool doFullDepthSearch;
	bool isPVMove;
	bool captureOrPromotion;
	int  moveCount;
	int  inCheck;
	int move_num=0x00;

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
	
	if( depth<=0 )
	{
		return qsearch( pos, ss, alpha, beta, 5, PVNode );
	}

	nodes++;
	
	// step1
	// initialize node
	moveCount = 0;
	inCheck   = is_in_check(pos);
	bestScore = -INFINITE;

	ss->currentMove = bestMove = 0;
	ss->ply = (ss-1)->ply + 1;
	(ss+1)->skipNullMove = false;
	(ss+1)->reduction = 0;
	(ss+2)->Killers[0] = (ss+2)->Killers[1] = 0;

	// step5
	// evaluate the position statically
	eval = ss->staticEval = evaluate(pos);
	
	// 王手がかかっていたら枝刈りしないため iid_start へ飛ぶ
	// 特に NullMovePruning には気をつける
	if( inCheck )
	{
		eval = ss->staticEval = -INFINITE;
		goto iid_start;
	}
	
	

	// step6
	// razoring
	if( !PVNode
		&& depth < 4 
		&& eval + razorMargin(depth) < beta
		&& abs(beta) < INFINITE - 300 )
	{
		const Score rbeta = beta - razorMargin(depth);
		const Score s = qsearch( pos, ss, rbeta-1, rbeta, 5, NonPV );
		if (s < rbeta) 
		{
			return s;
		}
	}
	
	// step7
	// static null move pruning
	if( !PVNode
		&& !ss->skipNullMove
		&& depth < 4
		&& beta <= eval - FutilityMargins[depth*2][0]
		&& abs(beta) < INFINITE - 300 )
	{
		return eval - FutilityMargins[depth*2][0];
	}
	
	//step8
	// null move
	if( !PVNode
		&& !ss->skipNullMove
		&& 2 <= depth
		&& beta <= eval
		&& abs(beta) < INFINITE - 300)
	{
		ss->currentMove = 0;
		Depth reduction = 3;

		if (beta < eval - 81) 
		{
			reduction += 1;
		}

		(ss+1)->skipNullMove = true;
		pos->color = 1 - pos->color;
		Score nullScore = ( depth - reduction < 1 ?
							-qsearch( pos, ss+1, -beta, -alpha, 5, NonPV )
							:-search( pos, ss+1, -beta, -alpha, depth - reduction, NonPV ));
		pos->color = 1 - pos->color;
		(ss+1)->skipNullMove = false;
		if (beta <= nullScore) 
		{
			if( depth < 6 )
			{
				return nullScore;
			}

			ss->skipNullMove = true;
			const Score s = search( pos, ss, alpha, beta, depth - reduction, NonPV );
			ss->skipNullMove = false;

			if (beta <= s) {
				return nullScore;
			}
		}
	}
	else {
		// fail low
		if( depth < 5 
			&& (ss-1)->reduction != 0)
		{
			return beta - 1;
		} 
	}
	
	/*
	// step9
	// probcut
	if( !PVNode
		&& 5<= depth
		&& !ss->skipNullMove
		&& abs(beta) < INFINITE - 200 )
	{
		Score mg = 150 + depth*25;    
        
		Depth rdepth = depth - 4;

		if( search( pos, ss, alpha-mg-1, alpha-mg, rdepth, NonPV ) < alpha-mg ){return alpha;}
		else if( search( pos, ss, beta+mg, beta+mg+1, rdepth, NonPV ) > beta+mg ){return beta;}
	}*/

iid_start:
	// step10
	// internal iterative deepning
	/*
	if((PVNode ? 5 : 8) <= depth 
		&& (PVNode || (!inCheck && beta <= ss->staticEval + 256)))
	{
		const Depth d = (PVNode ? depth - 2 : depth / 2);

		ss->skipNullMove = true;
		search( pos, ss, alpha, beta, d, (PVNode ? PV : NonPV) );
		ss->skipNullMove = false;
	}
	*/

	// step11
	// Loop through moves
	
	move_num += GenMoves( pos, &move[move_num] );	

	moveOrder( pos, ss, &move[0], move_num, depth );
	
	//===== All search ======================
	for( i=0; i<move_num; i++ )
	{	
		captureOrPromotion = ( GetCap(move[i]) && GetPro(move[i]) );

		// step13
		// futility pruning
		// todo: 条件をもっと絞るべき
		if( !PVNode
			&& !captureOrPromotion
			&& !inCheck 
			&& abs(bestScore) <= INFINITE - 300 )
		{
			// move count based pruning
			// todo: オーダリングの精度に依存するため外したほうが良いかも
			if( depth < 16 
				&& FutilityMoveCounts[depth*2] <= moveCount)
			{
				continue;
			}

			if( (pos->board[GetFrom(move[i])] != SOU ) && (pos->board[GetFrom(move[i])] != EOU ) )
			{
				if( eval + 416 <= alpha ){
					continue;    
				}
			}
		}
		// step14
		doMove( pos, move[i] );
		if( is_in_check(pos) ) 
		{ 
			undoMove( pos, move[i] );
			continue; 
		}
		moveCount++;

		isPVMove = (PVNode && moveCount == 1);

		doFullDepthSearch = !isPVMove;
		
		// step16
		// full depth search (PVS)
		if( doFullDepthSearch )
		{
			pos->color = 1 - pos->color;
			score = -search( pos, ss+1, -(alpha+1), -alpha, depth-1, NonPV ); 
			pos->color = 1 - pos->color;
		}
		
		if( PVNode && ( isPVMove || ( alpha<score && score<beta )) )
		{
			pos->color = 1 - pos->color;
			score = -search( pos, ss+1, -beta, -alpha, depth-1, PV ); 
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
		if (bestMove != ss->Killers[0]) {
			ss->Killers[1] = ss->Killers[0];
			ss->Killers[0] = bestMove;
		}
		//todo add killer and hash
	}

	return bestScore;
}

void init_searchOld(){
	
    int i,j;
	int d,mc;

	nodes=0;
	start=timeGetTime();
	for( i=0; i<32; i++ ){
		for( j=0; j<32; j++ ){
			pv[i][j]=0;
		}
	}

	for (d = 1; d < 16; ++d) {
		for (mc = 0; mc < 64; ++mc) {
			FutilityMargins[d][mc] = (int){ 112 * (int){ log( (double){d*d}/2 )  / log(2.0) + 1.001 } - 8 * mc + 45 };
		}
	}
	for (d = 0; d < 32; ++d){
		FutilityMoveCounts[d] = (int){ 3.001 + 0.3 * pow( (double)(d), 1.8) };
	}
	//if(AllTime>550000) MaxTime=8000;
	//else MaxTime=9800;
	MaxTime=9800;
}

void iterationOld( struct Position *pos )
{
    int depth,val;
	Score alpha,beta;
	int i;
	
	struct SearchStack ss[130];
	memset(ss, 0, 4*sizeof(struct SearchStack));

	Move best;

	depth=1;
	
	init_searchOld();

	while(1)
	{	
		ss->staticEvalRaw = INT_MAX;
		(ss+1)->staticEvalRaw = INT_MAX;
		alpha=-INFINITE;
		beta=INFINITE;
		//is_RootNode=true;
		
		val=search( pos, ss + 1, alpha, beta, depth, PV );
		if( val == -INFINITE + 3 || val == INFINITE - 3 )
		{
			send_best_to_usi(best);
			return;
		}
		else if(val==INFINITE)
        { 
			printf("info string ∩･ω･)∩わーい\n");
            send_pv_to_usi( pos, pv, val, depth, nodes );
            send_best_to_usi(pv[depth][depth]); 
            return; 
        }
		else if(val==-INFINITE){ printf("bestmove resign\n"); return; }
		
		send_pv_to_usi( pos, pv, val, depth, nodes );
		//printf("move:%d\n",pv[depth][depth]);
        best = pv[depth][depth];
		for( i=depth; i>0; i-- ){ pv[i+1][i+1]=pv[depth][i]; }
		depth++;
	}
}

