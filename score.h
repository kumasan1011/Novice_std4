
const Ply MaxPly = 128;
const Ply MaxPlyPlus4 = 132; //MaxPly + 4

// 評価値
enum {
	ScoreZero          = 0,
	ScoreDraw          = 0,
	ScoreMaxEvaluate   = 30000,
	ScoreMateLong      = 30002,
	ScoreMate1Ply      = 32599,
	ScoreMate0Ply      = 32600,
	ScoreMateInMaxPly  = ScoreMate0Ply - 128,
	ScoreMatedInMaxPly = -ScoreMateInMaxPly,
	ScoreInfinite      = 32601,
	ScoreNone          = 32602
};