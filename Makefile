#Makefile
Normal:
	gcc -Ofast -o Novice main.c board.c io.c genmove.c move.c bench.c debug.c search.c check.c evaluate.c -lm 