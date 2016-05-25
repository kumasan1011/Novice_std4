#include <stdio.h>
#include <string.h>
#include <sys/time.h>

unsigned long timeGetTime(){
	
	struct timeval tv;
	gettimeofday(&tv, NULL);
	unsigned long currTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return currTime;
}