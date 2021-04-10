/*
 * Thread 0 acorda alguma thread que esteja dormindo.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Flags auxiliares */
volatile int n_threads_dormindo = 0;  
volatile int thr0_ja_executou = 0;

#define N 15
pthread_cond_t cond;
pthread_mutex_t mutex;


void *thread_i(void* v) {
  int i = (int) v;

  sleep(random() % 5);  
  
  pthread_mutex_lock(&mutex);
  if (!thr0_ja_executou) {
    printf("Thread %d vai dormir... \n", i);
    n_threads_dormindo++;
    pthread_cond_wait(&cond, &mutex);
    n_threads_dormindo--;
    printf("Thread %d acordou. \n", i);
  }
  else
    printf("Thread %d não vai dormir.\n", i);
  pthread_mutex_unlock(&mutex);
  
  return NULL;
}

void *thread_0(void* v) {
  int j;

  sleep(N+1); 

  pthread_mutex_lock(&mutex);
  for (j = n_threads_dormindo; j > 0; j--) {
    /* printf("Thread 0 vai acordar alguma thread. \n"); */
    pthread_cond_signal(&cond);
  }
  thr0_ja_executou = 1;
  pthread_mutex_unlock(&mutex);
  
  return NULL;
}

int main() {
  pthread_t thr[N];
  int i;
  
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  for (i = 1; i < N; i++)
    pthread_create(&thr[i], NULL, thread_i, (void *) i);
  pthread_create(&thr[0], NULL, thread_0, NULL);

  for (i = 1; i < N; i++)
    pthread_join(thr[i], NULL);
  pthread_join(thr[0], NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  
  return 0;
}

