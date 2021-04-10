/*
 * Teste para locks recursivos.
 */
#include <stdio.h>
#include <unistd.h>

#include "lr.h"

rec_mutex_t lock;

void i() {
  rec_mutex_lock(&lock);
  printf("Passei pelos locks.\n");
  sleep(1);
  rec_mutex_unlock(&lock);
}

void h() {
  rec_mutex_lock(&lock);
  i();
  rec_mutex_unlock(&lock);
}

void g() {
  rec_mutex_lock(&lock);
  h();
  rec_mutex_unlock(&lock);
}

/* Sem o último unlock, deve bloquear
   a thread 1. */
void* f_thread0(void *v) {
  rec_mutex_lock(&lock);
  g();
  /* rec_mutex_unlock(&lock); */
  return NULL;
}

void* f_thread1(void *v) {
  rec_mutex_lock(&lock);
  g();
  rec_mutex_unlock(&lock);
  return NULL;
}

int main() {
  pthread_t thr0, thr1;

  rec_mutex_init(&lock);

  pthread_create(&thr0, NULL, f_thread0, NULL);
  pthread_create(&thr1, NULL, f_thread1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  return 0;
}
