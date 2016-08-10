#include <stdbool.h>

struct SearchStack {
    Move currentMove;
    Move Killers[2];
    bool skipNullMove;
    bool PVNode;
    Score staticEval;
    Ply ply;
    Depth depth;
};

