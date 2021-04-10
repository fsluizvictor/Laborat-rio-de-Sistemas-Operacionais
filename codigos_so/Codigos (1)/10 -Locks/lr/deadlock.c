/*
 * Deadlock de uma thread só.
 */
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* f_thread(void *v) {
  pthread_mutex_lock(&lock);
  pthread_mutex_lock(&lock);
  printf("Passei pelos locks...\n");
  return NULL;
}

int main() {
  pthread_t thr;
  
  if (pthread_create(&thr, NULL, f_thread, NULL))
    fprintf(stderr, "Erro na criação da thread.\n");

  if (pthread_join(thr, NULL))
    fprintf(stderr, "Erro na espera pela thread.\n");

  return 0;
}
