#include "define.h"


typedef int Ply;

const Ply MaxPly = 128;
const Ply MaxPlyPlus4 = MaxPly + 4;

// 評価値
enum Score {
	ScoreZero          = 0,
	ScoreDraw          = 0,
	ScoreMaxEvaluate   = 30000,
	ScoreMateLong      = 30002,
	ScoreMate1Ply      = 32599,
	ScoreMate0Ply      = 32600,
	ScoreMateInMaxPly  = ScoreMate0Ply - MaxPly,
	ScoreMatedInMaxPly = -ScoreMateInMaxPly,
	ScoreInfinite      = 32601,
	ScoreNotEvaluated  = INT_MAX,
	ScoreNone          = 32602
};