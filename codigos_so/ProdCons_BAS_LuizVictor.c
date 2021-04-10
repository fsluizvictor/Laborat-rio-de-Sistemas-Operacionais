/*
 * C�digo para produtor e consumidor sem nenhum tipo
 * de controle de concorr�ncia, mas com controle de bugs.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_ITENS 10
int buffer[N_ITENS];

int inicio = 0, final = 0;

void *produtor(void *v)
{
    int i;

    for (i = 0; i < 3 * N_ITENS; i++)
    {
        printf("Produtor, item = %d.\n", i);
        final = (final + 1) % N_ITENS;
        buffer[final] = i;
        sleep(random() % 3); /* Permite que a outra thread execute */
    }
    return NULL;
}

void *consumidor(void *v)
{
    int i, aux;

    for (i = 0; i < 3 * N_ITENS; i++)
    {
        inicio = (inicio + 1) % N_ITENS;
        aux = buffer[inicio]; /* Item � consumido */
        printf("Consumidor, item = %d.\n", aux);
        if (aux < i)
            printf("Erro: item foi consumido antes de ser produzido.\n");
        else if (aux > i)
            printf("Erro: item foi produzido antes de a posi��o estar livre.\n");
        sleep(random() % 3); /* Permite que a outra thread execute */
    }
    return NULL;
}

int main()
{
    int i;

    pthread_t thr_produtor, thr_consumidor;

    printf("Desenvolvido Luiz Victor");

    /* Limpa o buffer */
    for (i = 0; i < N_ITENS; i++)
        buffer[i] = 0;

    pthread_create(&thr_produtor, NULL, produtor, NULL);
    pthread_create(&thr_consumidor, NULL, consumidor, NULL);

    pthread_join(thr_produtor, NULL);
    pthread_join(thr_consumidor, NULL);

    return 0;
}
