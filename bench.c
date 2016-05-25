#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "define.h"
#include "winAPI.h"

void BenchGenMove(struct Position pos)
{
    
    int i;
    Move move[600];
    
	printf("Bench The Start position\n");
	int start=timeGetTime();
	for(i=0;i<1000000;i++){
		GenMoves( &pos, &move[0] );
	}
	int end=timeGetTime();
	double time=end-start;
	printf("  GenAllMoves : %.0lf(ms) , %.3lfM/s\n",time,(1000000*1000/time)/1000000);
}