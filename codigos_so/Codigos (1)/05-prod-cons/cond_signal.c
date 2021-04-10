/*
 * Thread 0 acorda Thread 1 (se ela estiver dormindo). 
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* Flags auxiliares */
volatile int thr1_dormindo   = 0;
volatile int thr0_ja_executou = 0;

pthread_cond_t cond;
pthread_mutex_t mutex;

void *thread_1(void* v) {

  pthread_mutex_lock(&mutex);
  if (!thr0_ja_executou) {
    printf("Thread 1 vai dormir... \n");
    thr1_dormindo = 1;
    pthread_cond_wait(&cond, &mutex);
    printf("Thread 1 acordou... \n");
  }
  pthread_mutex_unlock(&mutex);
  
  return NULL;
}

void *thread_0(void* v) {

  pthread_mutex_lock(&mutex);
  if (thr1_dormindo) {
    printf("Thread 0 vai acordar thread 1... \n");
    pthread_cond_signal(&cond);
  }
  thr0_ja_executou = 1;
  pthread_mutex_unlock(&mutex);
  
  return NULL;
}

int main() {
  pthread_t thr[2];

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  pthread_create(&thr[0], NULL, thread_0, NULL);
  pthread_create(&thr[1], NULL, thread_1, NULL);

  pthread_join(thr[1], NULL);
  pthread_join(thr[0], NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  
  return 0;
}

