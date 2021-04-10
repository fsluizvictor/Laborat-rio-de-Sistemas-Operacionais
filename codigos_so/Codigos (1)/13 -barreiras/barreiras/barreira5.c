/*
 * Como implementar barreiras de forma eficiente?
 * Quinta tentativa
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

sem_t sem_roleta_entrada;
sem_t sem_roleta_saida;

volatile int c;

void *f_thread(void* v) {
  int id = (int) v;
  int i, local_c;

  for (i = 0; i < 2; i++) {
    sleep(random() % 3);
    printf("Thread %d atingiu a barreira.\n", id);
    local_c = __sync_add_and_fetch (&c, 1);
    if (local_c == N) { 
      sem_wait(&sem_roleta_saida);
      sem_post(&sem_roleta_entrada);
    }

    sem_wait(&sem_roleta_entrada);
    sem_post(&sem_roleta_entrada);
    printf("Thread %d passou pela roleta de entrada.\n", id);

    local_c = __sync_sub_and_fetch (&c, 1);
    if (local_c == 0) { 
      sem_wait(&sem_roleta_entrada);
      sem_post(&sem_roleta_saida);
    }

    sem_wait(&sem_roleta_saida);
    sem_post(&sem_roleta_saida);
    printf("Thread %d passou pela roleta de saída.\n", id);
  }
  return NULL;
}

int main() {
  pthread_t thr[N];
  int i = 0;

  srandom(time(NULL));
  sem_init(&sem_roleta_entrada, 0, 0);
  sem_init(&sem_roleta_saida, 0, 1);
  for (i = 0; i < N; i++) 
    pthread_create(&thr[i], NULL, f_thread, (void*) i);

  pthread_exit(NULL);
}


