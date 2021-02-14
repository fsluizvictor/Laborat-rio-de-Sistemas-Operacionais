#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int conta = 0;

void *funcao1()
{
    int i;
    for (i = 0; i < 100000000; i++)
    {
        conta = conta + 3;
    }
    printf("Encerrei a thread 1\n");
    return 0;
}

void *funcao2()
{
    int i;
    for (i = 0; i < 100000000; i++)
    {
        conta = conta + 7;
    }
    printf("Encerrei a thread 2\n");
    return 0;
}

int main(int argc, char const *argv[])
{
    printf("\tDESENVOLVIDO POR: LUIZ VICTOR FERREIRA SANTOS\n");
    void *retval;
    pthread_t thread_a, thread_b;
    printf("PAI: Criando duas threads...\n");
    pthread_create(&thread_a, NULL, (void *)funcao2, NULL);
    pthread_create(&thread_b, NULL, (void *)funcao2, NULL);
    printf("Pai:Aguardando as duas threads...\n");
    pthread_join(thread_a, &retval);
    pthread_join(thread_b, &retval);
    printf("O valor da conta é: %d\n", conta);
    return 0;
}
