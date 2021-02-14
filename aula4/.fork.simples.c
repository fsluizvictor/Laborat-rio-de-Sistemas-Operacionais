#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	printf("DESENVOLVIDO POR LUIZ VICTOR\n");
	int id = fork();
	
	if(id == 0){
	printf("Filho: (pid=%d), espere 10 segundos!\n",getpid());
	sleep(10);
	printf("Filho: esperei e vou embora...\n");
	}
	else{
	printf("Pai: (pid=%d) e espero pelo filho=%d",getpid(),getppid());
	wait(NULL);
	printf("Pai: Meu filho terminou. Vouterminar também!");	
	}		
	return 0;
}
