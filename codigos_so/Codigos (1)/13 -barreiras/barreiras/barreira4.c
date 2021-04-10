/*
 * Como implementar barreiras de forma eficiente?
 * Quarta tentativa
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

sem_t sem_barreira;

volatile int c;

void *f_thread(void* v) {
  int id = (int) v;
  int i, local_c;

  for (i = 0; i < 2; i++) {
    sleep(random() % 3);
    printf("Thread %d atingiu a barreira.\n", id);
    local_c = __sync_add_and_fetch (&c, 1);
    if (local_c == N) sem_post(&sem_barreira);
    sem_wait(&sem_barreira);
    sem_post(&sem_barreira);
    local_c = __sync_sub_and_fetch (&c, 1);
    if (local_c == 0) sem_wait(&sem_barreira);
    printf("Thread %d passou pela barreira.\n", id);
    sleep(4);
  }
  return NULL;
}

int main() {
  pthread_t thr[N];
  int i = 0;

  srandom(time(NULL));
  sem_init(&sem_barreira, 0, 0);
  for (i = 0; i < N; i++) 
    pthread_create(&thr[i], NULL, f_thread, (void*) i);

  pthread_exit(NULL);
}


