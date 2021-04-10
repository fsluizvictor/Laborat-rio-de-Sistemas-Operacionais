/*
 * Implementa��o assim�trica do jantar dos fil�sofos.
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define N_CICLOS 8

sem_t sem_garfo[N];

/* Vari�veis extra para mostrar o estado da mesa */
sem_t sem_mesa;
enum pos_garfo
{
    ESQ,
    MESA,
    DIR
} pos_garfo[N];
char mesa[4 * N + 1];

/*
 *  garfo esq = phil_id
 *  garfo dir = (phil_id + 1) % N
 */

void print() //função para printar as situações
{
    printf("%s%c%c\n", &mesa[1], mesa[0], mesa[1]);
}

void fica_com_fome(int phil_id) //condição de espera para não haver confrontos
{
    sem_wait(&sem_mesa);         //semáforo é referenciado
    mesa[4 * phil_id + 3] = 'H'; //aloca-se mesas
    print();
    sem_post(&sem_mesa); //incrementa (desbloqueia) o semáforo apontado por sem .
    sleep(1);            // colocado em espera
}

void come(int phil_id) //condição para passar para o próximo filósofo
{
    sem_wait(&sem_mesa);         //semáforo é referenciado
    mesa[4 * phil_id + 3] = 'E'; //mesa é alocada
    print();
    sem_post(&sem_mesa); //incrementa (desbloqueia) o semáforo apontado por sem .
    sleep(1);            //colocado em espera
}

void pega_garfo_esq(int phil_id)
{
    sem_wait(&sem_garfo[phil_id]); //semáforo é referenciado
    sem_wait(&sem_mesa);           //semáforo é referenciado
    mesa[4 * phil_id] = ' ';       //mesa é alocada
    mesa[4 * phil_id + 1] = ' ';   //mesa é alocada
    mesa[4 * phil_id + 2] = '|';   //mesa é alocada
    print();
    sem_post(&sem_mesa); //incrementa (desbloqueia) o semáforo apontado por sem .
    sleep(1);            //colocado em espera
}

void pega_garfo_dir(int phil_id)
{
    int dir = (phil_id + 1) % N; //pega-se a referencia
    sem_wait(&sem_garfo[dir]);   //criado semáforo
    sem_wait(&sem_mesa);         //criado semáforo
    mesa[4 * dir] = '|';         //alocado mesa
    mesa[4 * dir + 1] = ' ';     //alocado mesa
    mesa[4 * dir + 2] = ' ';     //alocado mesa
    print();
    sem_post(&sem_mesa); //incrementa (desbloqueia) o semáforo apontado por sem .
    sleep(1);            //colocado em espera
}

void solta_garfos_pensa(int phil_id)
{
    int dir = (phil_id + 1) % N;   //pega-se a referencia
    sem_wait(&sem_mesa);           //criando semaforo
    sem_post(&sem_garfo[dir]);     //criando semaforo
    sem_post(&sem_garfo[phil_id]); //criando semaforo
    mesa[4 * phil_id] = ' ';       //aloca-se mesa
    mesa[4 * phil_id + 1] = '-';   //aloca-se mesa
    mesa[4 * phil_id + 2] = ' ';   //aloca-se mesa
    mesa[4 * dir] = ' ';           //aloca-se mesa
    mesa[4 * dir + 1] = '-';       //aloca-se mesa
    mesa[4 * dir + 2] = ' ';       //aloca-se mesa
    mesa[4 * phil_id + 3] = 'T';   //aloca-se mesa
    print();
    sem_post(&sem_mesa); //aloca-se mesa
    sleep(1);            //colocado me espera
}

void *f_phil(void *v)
{
    int phil_id = *(int *)v; //pega-se o valor de v
    int i;

    for (i = 0; i < N_CICLOS; i++) //ciclos que simulam o problema dos filósofos
    {
        fica_com_fome(phil_id);

        if (phil_id % 2)
        {
            pega_garfo_dir(phil_id);
            pega_garfo_esq(phil_id);
        }
        else
        {
            pega_garfo_esq(phil_id);
            pega_garfo_dir(phil_id);
        }
        come(phil_id);

        solta_garfos_pensa(phil_id);
    }

    return NULL;
}

int main()
{
    pthread_t thr[N];
    int i, phil_id[N];

    printf("Desenvolvido por Luiz Victor");

    sem_init(&sem_mesa, 0, 1);//inicializa o problema
    for (i = 0; i < N; i++)//aloca-se as mesas
    {
        sem_init(&sem_garfo[i], 0, 1);
        pos_garfo[i] = MESA;
        mesa[4 * i] = ' ';
        mesa[4 * i + 1] = '-';
        mesa[4 * i + 2] = ' ';
        mesa[4 * i + 3] = 'T';
    }
    mesa[4 * N] = 0;

    for (i = 0; i < N; i++)
    {
        phil_id[i] = i;
        pthread_create(&thr[i], NULL, f_phil, (void *)&phil_id[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(thr[i], NULL);

    for (i = 0; i < N; i++)
        sem_destroy(&sem_garfo[i]);
    sem_destroy(&sem_mesa);

    return 0;
}
