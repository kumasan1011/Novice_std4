#include <stdbool.h>

Score orderPieceVal[]={ 0, 87,232,257,369,444,569,642,15000,534,489,510,495,0,827,945,
                           87,232,257,369,444,569,642,15000,534,489,510,495,0,827,945
                      };

Piece orderPiece[]={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15  };

Piece orderMovePiece[]={ 0,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                           15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

struct SearchStack {
    Move currentMove;
    Move Killers[2];
    Move excludedMove;
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