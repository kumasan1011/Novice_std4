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
Depth Reductions[2][64][64];
Score History[2][32][256]; //[Color][PieceType][To]

#define reduct( PVNode, depth, moveCount ) Reductions[PVNode ? 1:0][depth][(moveCount<63) ? moveCount : 63 ]
#define futilityMargin( depth )  ( depth * 180 )

/* Novice_wcsc26_final の探索 */
int hash_hit;
uint64 MaxTime;
uint64 FullTime = 0;
uint64 start;
uint64 nodes;
Move pv[32][32];


void swap( int *a, int *b )
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void moveOrder( struct Position *pos, struct SearchStack *ss, Move *move, int end_num, Depth depth, Move hashMove )
{	
	int i,j;
	int Val[768];
	int max,maxid;
	
	for( i=0; i<end_num; i++ )
	{
		if(move[i]==pv[depth][depth]){	Val[i]=100000; continue; }
		if(move[i]==hashMove){	Val[i]=99999; continue; }
		//TODO  here is good_cap (SEE>0) move 
		if(move[i]==ss->Killers[0]){ Val[i]=4000; continue; }
		if(move[i]==ss->Killers[1]){ Val[i]=3500; continue; }
		//counterMove
		//if( GetTo(move[i])==GetTo((ss-1)->currentMove) ){  Val[i]=1000; continue; }
		
		// When Cap>=Piece, use MVV/LVA. 
		// This is more effective way than SEE in this case.
		if( orderPiece[GetCap(move[i])] >= orderPiece[pos->board[GetFrom(move[i])]] )
		{
			Val[i]  = orderPieceVal[GetCap(move[i])]*orderMovePiece[pos->board[GetFrom(move[i])]];
			Val[i] += 5000;
			// if this move is promotion move, add val of diff between pro and non-pro.
			//if( GetPro(move[i]) )
		}/*
		//桂馬以上を取る場合も優先する
		else if( orderPiece[GetCap(move[i])] >= KE ){
			Val[i]  = orderPieceVal[GetCap(move[i])]*orderMovePiece[pos->board[GetFrom(move[i])]];
			Val[i] += 3000;
		}*/
		else {
			Val[i] = History[pos->color][pos->board[GetFrom(move[i])]][GetTo(move[i])];
		}
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
	
	int standpat=evaluate(pos);
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
	Move move[768];
	//for(i=0;i<768;i++){ move[i]=0;}
	int move_num=0x00;
	move_num+=GenOnlyMoves( pos, &move[move_num] );
    
	for(i=0;i<move_num;i++){
		// When Cap>=Piece, use MVV/LVA. 
		// This is more effective way than SEE in this case.
		if( orderPiece[GetCap(move[i])] >= orderPiece[pos->board[GetFrom(move[i])]] )
		{
			Val[i]  = orderPieceVal[GetCap(move[i])]*orderMovePiece[pos->board[GetFrom(move[i])]];
			Val[i] += 5000;
			// if this move is promotion move, add val of diff between pro and non-pro.
			//if( GetPro(move[i]) )
		}
		//桂馬以上を取る場合も優先する
		else if( orderPiece[GetCap(move[i])] >= KE ){
			Val[i]  = orderPieceVal[GetCap(move[i])]*orderMovePiece[pos->board[GetFrom(move[i])]];
			Val[i] += 3000;
		}
		else {
			Val[i] = History[pos->color][pos->board[GetFrom(move[i])]][GetTo(move[i])];
		}
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
		
		doMove( pos, move[i] );

		if( !GetCap(move[i]) )
		{ 
			undoMove( pos, move[i] );
			continue; 
		}

		if(is_in_check( pos )) 
		{ 
			undoMove( pos, move[i] );
			continue; 
		}
		else 
        {

            pos->color = 1 - pos->color;
            val=-qsearch( pos, ss+1, -beta, -alpha, depth-1, PVNode ); 
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
	Move excludedMove;
	Move movesSearched[64];
	Move move[768];
	bool doFullDepthSearch;
	bool isPVMove;
	bool captureOrPromotion;
	bool singularExtensionNode;
	int  moveCount;
	int  playMoveCount;
	int  inCheck;
	int  isGiveCheck;
	int  move_num=0x00;

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
		return qsearch( pos, ss, alpha, beta, 7, PVNode );
	}

	nodes++;
	
	// step1
	// initialize node
	moveCount = playMoveCount = 0;
	inCheck   = is_in_check(pos);
	bestScore = -INFINITE;

	ss->currentMove = bestMove = (ss+1)->excludedMove = 0;
	ss->ply = (ss-1)->ply + 1;
	(ss+1)->skipNullMove = false;
	(ss+1)->reduction = 0;
	(ss+2)->Killers[0] = (ss+2)->Killers[1] = 0;

	// step4
	// transposition table look up
	excludedMove = ss->excludedMove;
	Move hash_move = 0;
	struct HashEntry *phash = NULL;
	
	// 現在の局面のハッシュ値をキーに、ハッシュテーブルを引く
	if( hash_probe( pos->hashkey, pos->color, alpha, beta, depth, &phash) == 1 )
	{
		// 利用可能なハッシュがあった。
		pv[depth][depth] = phash->best;
		hash_hit++;
		return phash->score;
	}
	if(phash)
	{
		hash_move  = phash->best;
	}

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
		&& !phash
		&& depth < 4 
		&& eval + razorMargin(depth) <beta )
	{
		const Score rbeta = beta - razorMargin(depth);
		const Score s = qsearch( pos, ss, rbeta-1, rbeta, 5, NonPV );
		if (s <= rbeta) 
		{
			return s;
		}
	}
	
	// 6.5
	if( depth < 2  )
	{
		if( beta + 200 <= eval )
		{
			return beta;
		}
	} else if ( depth < 3 && !PVNode ) {
		
		Score bound=beta + 416;
		
		Score v = qsearch( pos, ss, bound-1, bound, 7, NonPV );
		if( bound <= v )
		{
			return beta;
		}
	}

	// step7
	// static null move pruning
	if( !PVNode
		&& !ss->skipNullMove
		&& depth < 7
		&& beta <= eval - futilityMargin(depth) )
	{
		return eval - futilityMargin(depth);
	}
	
	//step8
	// null move
	if( !PVNode
		&& !ss->skipNullMove
		&& 2 <= depth
		&& beta <= eval )
	{
		ss->currentMove = 0;
		Depth reduction = 4;

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
			&& !hash_move
			&& (ss-1)->reduction != 0)
		{
			return beta - 1;
		} 
	}
	
	
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
	}

iid_start:
	// step10
	// internal iterative deepning
	if((PVNode ? 5 : 8) <= depth
		&& !phash //果たしてこれは要るのか？
		&& !hash_move
		&& (PVNode || (!inCheck && beta <= ss->staticEval + 256)))
	{
		const Depth d = (PVNode ? depth - 2 : depth / 2);

		ss->skipNullMove = true;
		search( pos, ss, alpha, beta, d, (PVNode ? PV : NonPV) );
		ss->skipNullMove = false;

		hash_probe( pos->hashkey, pos->color, alpha, beta, depth, &phash);
		
		if(phash)
		{
			hash_move  = phash->best;
		}
	}

	score = bestScore;
	singularExtensionNode =
		   8 <= depth
		&& !excludedMove
		&& !hash_move
		&& 0 <= phash->flag //hash_exact or hash_upperBound
		&& depth - 3 <= phash->rdepth;


	// step11
	// Loop through moves
	
	move_num += GenMoves( pos, &move[move_num] );	

	moveOrder( pos, ss, &move[0], move_num, depth, hash_move );
	
	//===== All search ======================
	for( i=0; i<move_num; i++ )
	{	

		if ( move[i] == excludedMove ) 
		{
			continue;
		}

		captureOrPromotion = ( GetCap(move[i]) && GetPro(move[i]) );
		extension = 0;

		// step12
		// singular extension
		if ( singularExtensionNode
			 && extension == 0
			 && move[i] == hash_move  )
		{
			const Score rBeta = phash->score - 2 * (Score){depth};
			ss->excludedMove = move[i];
			ss->skipNullMove = true;
			score = search( pos, ss, rBeta - 1, rBeta, depth / 2, NonPV );
			ss->skipNullMove = false;
			ss->excludedMove = 0;

			if (score < rBeta) 
			{
				extension = 1;
			}
		}

		newDepth = depth - 1 + extension;

		++moveCount;
		
		if( !PVNode
			&&depth < 3 
			&& !inCheck
			&& !captureOrPromotion)
		{
			Score mg;
			
			if( (pos->board[GetFrom(move[i])] != SOU ) && (pos->board[GetFrom(move[i])] != EOU ) ) mg=1600;
			else mg=416;
			
			if( eval + mg <= alpha )
			{
				continue;    
			}
		}
		
		/*
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
				&& FutilityMoveCounts[ depth*3 < 31 ? depth*3 : 31 ] <= moveCount)
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
		*/
		// step14
		doMove( pos, move[i] );
		if( is_in_check(pos) ) 
		{ 
			undoMove( pos, move[i] );
			continue; 
		}

		playMoveCount++;

		isPVMove = (PVNode && moveCount == 1);
		ss->currentMove  = move[i];
		
		if ( playMoveCount < 64)
		{
			movesSearched[playMoveCount++] = move[i];
		}

		
		//step15
		// LMR
		if( 3 <= depth
			&& !isPVMove
			&& !captureOrPromotion
			&& move[i] != hash_move
			&& ss->Killers[0] != move[i]
			&& ss->Killers[1] != move[i] )
		{
			ss->reduction = reduct( PVNode, depth-1, moveCount );
			const Depth d = (( newDepth - ss->reduction > 2 ) ? newDepth - ss->reduction : 2);

			//PVS
			pos->color = 1 - pos->color;
			score = -search( pos, ss+1, -(alpha+1), -alpha, d, NonPV ); 
			pos->color = 1 - pos->color;
			
			doFullDepthSearch = (alpha < score && ss->reduction != 0);
			ss->reduction = 0;
		}
		else {
			doFullDepthSearch = !isPVMove;
		}
		
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
		hash_add( pos->hashkey, pos->color, bestScore, alpha, beta, depth, bestMove );

		if( GetCap(bestMove) && GetPro(bestMove) )
		{
			if (!inCheck && bestMove != ss->Killers[0]) 
			{
				ss->Killers[1] = ss->Killers[0];
				ss->Killers[0] = bestMove;
			}

			const Score bonus = depth*depth;

			History[pos->color][pos->board[GetFrom(bestMove)]][GetTo(bestMove)] += bonus;
			
			
			for ( i = 0; i < playMoveCount - 1; ++i ) 
			{
				const Move m = movesSearched[i];
				History[pos->color][pos->board[GetFrom(bestMove)]][GetTo(bestMove)] -= bonus;
			}
		}	
	}

	return bestScore;
}

void init_searchOld(){
	
    int i,j,k;
	int imp,d,hd,mc;
	
	for( hd = 1; hd < 64; hd++ )
	{
		for( mc = 1; mc < 64; mc++ )
		{
			double    pvRed = log((double)hd) * log((double)mc) / 3.0;
			double nonPVRed = 0.33 + log((double)hd) * log((double)mc) / 2.25;
			Reductions[1][hd][mc] = (int) (   pvRed >= 1.0 ? floor(    pvRed ) : 0);
			Reductions[0][hd][mc] = (int) (nonPVRed >= 1.0 ? floor( nonPVRed )  : 0);
		}
	}
	
	/*
	for( hd = 1; hd < 64; hd++ )
	{
		for( mc = 1; mc < 64; mc++ )
		{
			double   r = log(hd) * log(mc) /2;
			if( r < 0.80 ) continue;

			Reductions[0][hd][mc] = (int) r;
			Reductions[1][hd][mc] = (int) ( Reductions[0][hd][mc] >= 1.0 ? Reductions[0][hd][mc] : 0);
		}
	}
	*/

	hash_hit = 0;
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

	for( i=0; i<2; i++ )
	{
		for( j=0; j<32; j++ )
		{
			for( k=0; k<256; k++ )
			{
				History[i][j][k] = 0;
			}
		}
	}
	if ( FullTime < 2000 ) MaxTime=1800;
	else if ( FullTime > 880000 ) MaxTime = 8000; // 10 sec limits
	else MaxTime = 15000;
	//MaxTime=14000;
	//MaxTime = 29800;
	//MaxTime = 3000;
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
			int current=timeGetTime();
			int usi_time=current-start;
			FullTime += usi_time;
			send_best_to_usi(best);
			return;
		}
		else if(val==INFINITE)
        { 
			printf("info string ∩･ω･)∩わーい\n");
            send_pv_to_usi( pv, val, depth, nodes );
            send_best_to_usi(pv[depth][depth]); 
            return; 
        }
		else if(val==-INFINITE){ printf("bestmove resign\n"); return; }
		
		send_pv_to_usi( pv, val, depth, nodes );
		//printf("hash_hit:%d\n",hash_hit);
		//printf("move:%d\n",pv[depth][depth]);
        best = pv[depth][depth];
		for( i=depth; i>0; i-- ){ pv[i+1][i+1]=pv[depth][i]; }
		depth++;
	}
}

