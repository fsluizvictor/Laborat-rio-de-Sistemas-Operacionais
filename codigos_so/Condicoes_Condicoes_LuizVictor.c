#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000 // constante

int count = 0; // é declarado um contador

void *ThreadAdd(void *a)//função que recebe void
{
    int i, tmp;//variáveis 
    for (i = 0; i < N; i++)
    {
        tmp = count; /* estas 3 linhas vÃ£o criar um problema de condiÃ§Ã£o de corrida */
        tmp = tmp + 1;
        count = tmp; /* ao final, espera-se que o contador count seja incrementado N vezes */
    }
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;// declarado arquivos que recebem informações de threads

    printf("Desenvolvido por Luiz Victor");

    if (pthread_create(&tid1, NULL, ThreadAdd, NULL))//é testado se a função de criação deu verdadeiro
    {
        printf("\nErro criando Thread 1\n");// caso true é printado em tela
        exit(1);
    }

    if (pthread_create(&tid2, NULL, ThreadAdd, NULL))//é testado se a função de criação deu verdadeiro
    {
        printf("\nErro criando Thread 2\n");// caso true é printado em tela
        exit(1);
    }

    if (pthread_join(tid1, NULL)) /* aguarda o fim da Thread 1 */
    {
        printf("\n ERROR joining thread");//escrito erro em tela
        exit(1);
    }

    if (pthread_join(tid2, NULL)) /* aguarda o fim da Thread 2 */
    {
        printf("\n ERROR joining thread");//escrito erro tela
        exit(1);
    }

    if (count != 2 * N) /* como foram duas threads, espera-se que o contador seja 2*N */
        printf("\n OPS! o contador Ã© [%d], deveria ser %d\n", count, 2 * N);
    else
        printf("\n OK! contador Ã© [%d]\n", count);

    pthread_exit(NULL);
}
