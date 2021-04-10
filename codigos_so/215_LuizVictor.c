#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMBER_OF_THREADS 10
    void *
    print_hello_world(void *tid)
{
    printf("Desenvolvido por Luiz Victor\n");
    /* Esta funcao imprime o identificador do thread e sai. */
    printf("Ola mundo. Boas vindas do thread %d\n", tid);
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    /* O programa principal cria 10 threads e sai. */
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;//referencia para contadores e variáveis auxiliares

    for (i = 0; i < NUMBER_OF_THREADS; i++)//estrutura de repetição para criar thread
    {
        printf("Metodo Main. Criando thread %d\n", i);//printa em tela o némero do contador de thread
        status = pthread_create(&threads[i], NULL, print_hello_world, (void *)i);//é pego os status da thread no momento exato
        if (status != 0)// testa se é diferente de 0 o retorno, pois assim se sabe se deu certo ou n
        {
            printf("Oops. pthread_create returned error code %d\n", status);//printa em tela os status
            exit(-1);//sai da condicional
        }
    }
    exit(NULL);
}