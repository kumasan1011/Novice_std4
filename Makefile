#Makefile
Normal:
	gcc -Ofast -o Novice main.c bench.c board.c check.c debug.c evaluate.c genmove.c io.c move.c piecemove.c search.c tt.c -lm 
debug:
	gcc -O0 -o Novice main.c bench.c board.c check.c debug.c evaluate.c genmove.c io.c move.c piecemove.c search.c tt.c -lm -g