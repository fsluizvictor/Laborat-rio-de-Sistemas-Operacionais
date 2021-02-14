#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int id = fork();
	printf("Pai: (pid=%d) vou criar um processo filho...\n",getpid());
	
	if(id == 0){
	printf("\tFilho: (pid=%d) vou passar 5 segundos.\n",getpid());
	sleep(5);
	printf("\tFilho: vou terminar...\n");	
	}
	else{
	printf("Pai: não vou executar wait...");
	for(;;)
	{
	}
	wait(NULL);
	}
	return 0;
	

}
