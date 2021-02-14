#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void funcao1(char *str)
{
    printf("\tFilha1: vou aguardar 5 segundos...\n");
    sleep(5);
    printf("\tFilha1: já aguardei agora vou finalizar...\n");
}

void funcao2(char *str)
{
    printf("\tFilha2: vou aguardar 10 segundos...\n");
    sleep(10);
    printf("\tFilha2: já aguardei agora vou finalizar...\n");
}
int main()
{
    printf("DESENVOLVIDO POR: LUIZ VICTOR FERREIRA SANTOS");
    void *retval;
    pthread_t thread_a, thread_b;
    printf("PAI: criando duas threads...\n");
    pthread_create(&thread_a, NULL, (void *)funcao1, NULL);
    pthread_create(&thread_b, NULL, (void *)funcao2, NULL);
    printf("Pai: Aguardando as duas threads...\n");
    pthread_join(thread_a, &retval);
    pthread_join(thread_b, &retval);
    printf("Pai: Ambas as threads terminaram...\n");
    return 0;
}
