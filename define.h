//macro
typedef unsigned long long uint64;
typedef unsigned long long Hash;
typedef unsigned int  Move; 
typedef int Board;
typedef int Score;

enum Color { Black, White, Color_NB };

struct Position {
  Board pos[256]; //実体
  Board piecePos[64]; //駒番号（使用するのは40個）とその位置
  Board pieceCol[64]; //駒番号とその色
  Hash hashkey; 
};