#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "define.h"
#include "tt.h"

struct HashEntry hash[Color_NB][HASH_SIZE];

// ハッシュのタイプ
enum {
	HASH_LOWER=-1,	// 下限
	HASH_EXACT,	// 真値
	HASH_UPPER	// 上限
};


// ハッシュ値の参照
int hash_probe( Hash hash_key, Color color, Score alpha, Score beta, Depth rdepth, struct HashEntry **phash )
{	
	Hash hash_index = hash_key & HASH_MASK;
	*phash = &hash[color][hash_index];
	
	if((*phash)->hash_key == hash_key)
    {
		//if( !hash[turn][hash_index].best ) printf("error\n");
		// 利用可能な品質かどうかチェック
		// ①現在の局面のそこから先の深さが、テーブルと同じか、それよりも深いこと
		// ②評価値が
		//   (a)α以下ならば、真値か上限であること
		//   (b)α～βならば、真値であること
		//   (c)β以上ならば、真値か下限であること
		if(	rdepth <= (*phash)->rdepth 
            && (((*phash)->score <= alpha && (*phash)->flag > 0) 
			    || (*phash)->flag == 0 || ((*phash)->score  >= beta && (*phash)->flag < 0)))
        {
			return 1; 
		}
	}
	return 0;
}
// ハッシュの登録
void hash_add( Hash hash_key, Color color, Score score, Score alpha, Score beta, Depth rdepth, Move move )
{	
	Hash hash_index = hash_key & HASH_MASK;
	struct HashEntry ret = hash[color][hash_index];
	
	if( ret.rdepth <= rdepth )
    {
		// 情報登録
		ret.hash_key = hash_key;
		ret.rdepth   = (char)rdepth;
		ret.score    = score;
		ret.best     = move;

		// 登録されるハッシュ内容の種類
		// αβ内に収まっていれば、その評価値は正確であるので、
		// ハッシュ参照時は、その評価値をそのまま返せばよい。
		// それ以外は、真の評価値と違う可能性がある。
		if(score <= alpha)
        {
			// 全ての手を評価しても、その最大評価値がα以下だった場合
			ret.flag     = (char)HASH_UPPER;
			
		} else if(score >= beta){
			// βカットが起きた場合
			ret.flag     = (char)HASH_LOWER;
		} else {
			// 全ての手を評価して、最大評価値がα～β内に収まった場合
			ret.flag     = (char)HASH_EXACT;
		}
		hash[color][hash_index]=ret;
	}
}