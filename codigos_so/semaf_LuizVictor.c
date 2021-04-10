#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000

int count = 0;

void * ThreadAdd(void * a)
{
    int i, tmp;
    for(i = 0; i < N; i++)
    {
        tmp = count;      /* estas 3 linhas vÃ£o criar um problema de condição de corrida */
        tmp = tmp+1;      
        count = tmp;      /* ao final, espera-se que o contador count seja incrementado N vezes */ 
    }
}

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;

    printf("Desenvolvido por Luiz Victor");

    if(pthread_create(&tid1, NULL, ThreadAdd, NULL)) // Verifica se a thread 1 foi criada com sucesso
    {
      printf("\nErro criando Thread 1\n"); // Exibe uma mensagem de erro caso não
      exit(1);
    }

    if(pthread_create(&tid2, NULL, ThreadAdd, NULL)) // Verifica se a thread 2 foi criada com sucesso
    {
      printf("\nErro criando Thread 2\n"); // Exibe uma mensagem de erro caso não
      exit(1);
    }

    if(pthread_join(tid1, NULL))    /* aguarda o fim da Thread 1 */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* aguarda o fim da Thread 2 */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if (count != 2 * N)  /* como foram duas threads, espera-se que o contador seja 2*N */
        printf("\n OPS! o contador Ã© [%d], deveria ser %d\n", count, 2*N);
    else
        printf("\n OK! contador Ã© [%d]\n", count);
  
    pthread_exit(NULL);
}