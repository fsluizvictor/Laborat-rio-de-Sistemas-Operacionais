/*
 * Teste da função pthread_barrier_wait
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

pthread_barrier_t *barrier;
volatile int c;

void *f_thread(void* v) {
  int id = (int) v;
  int i;

  for (i = 0; i < 2; i++) {
    sleep(v);
    printf("Thread %d atingiu a barreira.\n", id);
    pthread_barrier_wait(&barrier);
    printf("Thread %d passou pela barreira.\n", id);
  }
  return NULL;
}

int main() {
  pthread_t thr[N];
  int i = 0;

  srandom(time(NULL));
  pthread_barrier_init(&barrier, NULL, N);
  for (i = 0; i < N; i++) 
    pthread_create(&thr[i], NULL, f_thread, (void*) i);

  pthread_exit(NULL);
}


