#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	printf("DESENVOLVIDO POR LUIZ VICTOR");
	       
 	int id = fork();
        printf("Pai: (pid=%d) vou criar um processo filho...\n",getpid());

        if(id == 0){
        printf("\tFilho: (pid=%d) \n",getpid());
        printf("\tFilho: ficar me loop infinito...\n");   
	
	for(;;);        
	}
        else{
        sleep (5);
	printf("Pai: (pid=%d) vou deixar o meu filho orfão.\n",getpid());
        }
        
        return 0;


}

