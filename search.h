#include <stdbool.h>

struct SearchStack {
    Move currentMove;
    Move Killers[2];
    bool skipNullMove;
    bool PVNode;
    Score staticEval;
    Ply ply;
    Depth reduction;
    Depth depth;
    Score staticEvalRaw;
};


#define NonPV false
#define PV    true
#define razorMargin(depth) ( 512 + 16*depth )