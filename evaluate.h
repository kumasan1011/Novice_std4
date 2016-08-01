#ifndef _EVALUATE_H_
#define _EVALUATE_H_


int PieceOnlyVal[]={ 0,100,200,220,300,350,600,700,15000,240,290,300,350,0,800,950 };

int PieceVal[]={ 0, 87,232,257,369,444,569,642,15000,534,489,510,495,0,827,945 };

int PieceHandVal[]={ 0, 87,232,257,369,444,569,642 };

int RankBonus[]={ 0, 0, 0, 0, 150, 450, 900,1300,1550,1600 };

int evaluate( struct Position *ptree );

#endif //_EVALUATE_H_