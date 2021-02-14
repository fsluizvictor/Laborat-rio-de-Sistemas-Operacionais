#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *funcao_thread(void *arg)
{
	printf("\t FILHA: soua a nova thread e aguardarei 10s\n");
	sleep(10);
	printf("\tFILHA: terminarei agora\n");
	return NULL;
}

int main()
{
	printf("DESENVOLVIDO POR: LUIZ VICTOR FERREIRA SANTOS");
	pthread_t thread;
	printf("PAI: criando uma nova thread...\n");
	pthread_create(&thread, NULL, &funcao_thread, NULL);

	printf("PAI: aguardando a conclusão da thread...\n");
	pthread_join(thread, NULL);
	printf("PAI: a thread terminou. Vouterminar também.");
	return 0;
}
