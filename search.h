#include"define.h"

struct SearchStack {
    Move currentMove;
    Move Killers[2];
    bool skipNullMove;
    Ply ply;
    Depth depth;
};