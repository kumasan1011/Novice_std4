#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#include "define.h"

/*
bool IsStopReceived=false;
bool IsGoInfinite=false;


void *ReceiveThread(void *a)
{
    
    int i;
    
    while(1)
    {
        char buf[10000];
		setvbuf(stdout, NULL, _IONBF, 0); 
		if( fgets(buf, 10000, stdin)!=NULL ){ buf[strlen(buf) - 1]=0; }
        
        if (strncmp(buf, "stop", strlen("stop")) == 0) 
        {
			IsStopReceived = true;
            break;
		}
        else if( strncmp(buf,"quit",strlen("quit"))==0 )
        {
			exit(1);
		}
    }
}*/

int main()
{
	
	int i;
	int turn;
	
	while(1)
    {
		char buf[10000];
		setvbuf(stdout, NULL, _IONBF, 0); 
		if( fgets(buf, 10000, stdin)!=NULL ){ buf[strlen(buf) - 1]=0; }
		
		int len=strlen(buf);
		
		struct Position pos;
		
		if( strncmp( buf,"usi",len )==0 ) 
        {
			printf("id name Novice_beta\n");
			printf("id author Kumagai Hirotaka\n");
			printf("option name ValueType type combo default Komadoku var Komadoku var fv.bin\n");
			printf("usiok\n");
		}
        
        /*
        else if(strncmp(buf, "setoption", strlen("setoption")) == 0) 
        {
            eval_mode=mode_komadoku;
			if(strncmp(buf, "setoption name ValueType value Komadoku", len) == 0) 
            {
				eval_mode=mode_komadoku;
			}
            else if (strncmp(buf, "setoption name ValueType value fv.bin", len) == 0) 
            {
				eval_mode=mode_fv;
			}
		}
        else if( strncmp( buf,"isready",len )==0 ) 
        {
			AllTime=0;
			init_hash_key();
			if( eval_mode==mode_fv )
            {
				if( load_fv()==-2 ){ printf("load_error\n"); }
			}
			printf("readyok\n");
		}*/
        else if( strncmp(buf,"position",strlen("position"))==0 ) 
        {
			if( strncmp(buf,"position startpos",strlen("position startpos"))==0 )
            {
				InitBoard(&pos);
				make_usi_position( buf, &pos );
				//set_hash();
				PrintBoard(pos);
			}
            else if( strncmp(buf,"position sfen",strlen("position sfen"))==0 )
            {
				InitBoard(&pos);
				make_sfen_position( buf, &pos );
				//set_hash();
				PrintBoard(pos);
			}
			continue;
		}
		/*
        else if(strncmp(buf, "go", strlen("go")) == 0) 
        {
            if(strncmp(buf, "go infinite", strlen("go infinite")) == 0) { IsGoInfinite=true; }
            IsStopReceived=false;
            pthread_t pthread;
            pthread_create( &pthread, NULL, &ReceiveThread, NULL);
            iteration(turn);
            pthread_cancel(pthread);
        }*/
        else if(strncmp(buf, "bench", strlen("bench")) == 0) 
        {
			/*
            init_hash_key();
            if(strncmp(buf, "bench search", strlen("bench search")) == 0) 
            {
                IsGoInfinite=true;
				IsStopReceived=false;
				eval_mode=mode_fv;
				if( load_fv()==-2 ){ printf("load_error\n"); }
				pthread_t pthread;
            	pthread_create( &pthread, NULL, &ReceiveThread, NULL);
                search_bench(turn);
				pthread_cancel(pthread);
            }
            else*/ if(strncmp(buf, "bench genmove", strlen("bench genmove")) == 0) 
            {
                BenchGenMove(pos);
            }
		}
        else if( strncmp(buf,"quit",strlen("quit"))==0 )
        {
			break;
		}
		else if( strncmp(buf,"position",strlen("position"))==0 )
		{
			InitBoard(&pos);
			make_sfen_position( &buf, &pos );
			PrintBoard(pos);
		}
		else if( strncmp(buf,"debug",strlen("debug"))==0 )
		{
			// testcode
			struct Position pos0;
			copyPosStruct( pos, &pos0 );
			Move move = d_move(&pos);
			//PrintBoard(pos);
			undoMove( &pos, move );
			confPosStruct( pos, pos0 );
			//PrintBoard(pos);
		}
		/*
		Move move[600];
		int num = GenMoves(  &pos, &move[0] );
		PrintAllMoves( &move[0], num );
		*/
		//BenchGenMove(pos);
	}
	
	return 0;
}