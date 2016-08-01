#Makefile
Normal:
	gcc -Ofast -o Novice main.c bench.c board.c check.c debug.c evaluate.c genmove.c io.c move.c search.c  -lm 