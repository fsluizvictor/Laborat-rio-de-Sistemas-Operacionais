#include <stdio.h>
#include <unistd.h>

int main(){
	printf("DESENVOLVIDO POR LUIZ VICTOR\n");
	printf("PROCESSO PID %d\n",getpid());
	printf("PID DO PAI %d\n",getppid() );
	printf("GRUPO ID %d\n",getpgrp());
	return 0;
}
