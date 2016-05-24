#ifndef _IO_H_
#define _IO_H_

static char PieceName[][3]={ "[]","FU","KY","KE","GI","KI","KA","HI","OU","TO","NY","NE","NG","NK","UM","RY" };
static char PieceName2[][3]={ "[]","fu","ky","ke","gi","ki","ka","hi","ou","to","ny","ne","ng","nk","um","ry" };
static char RankName[][2]={ " ","a","b","c","d","e","f","g","h","i" };
static char UsiPieceName[][2]={ " ","P", "L", "N", "S", "G", "B", "R", "K" };

static char UsiPieceName1[]={ ' ','P', 'L', 'N', 'S', 'G', 'B', 'R', 'K' };
static char UsiPieceName2[]={ ' ','p', 'l', 'n', 's', 'g', 'b', 'r', 'k' };
static char UsiRankName[]={ 'a','b','c','d','e','f','g','h','i' };

void PrintBoard( struct Position );

#endif //_IO_H_