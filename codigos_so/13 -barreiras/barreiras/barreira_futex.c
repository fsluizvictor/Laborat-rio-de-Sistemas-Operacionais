/*
 * Como implementar barreiras de forma eficiente?
 * Tentativa com futex
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/futex.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <limits.h>

/* Retorna -1 se o futex não bloqueou e 
            0 caso contrário */
int futex_wait(volatile void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, 
                 val1, NULL, NULL, 0);
}

/* Retorna o número de threads que foram acordadas */
int futex_wake(volatile void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, 
                   n, NULL, NULL, 0);
}

#define N 10

volatile int roleta_entrada;
volatile int roleta_saida;

volatile int c;

void *f_thread(void* v) {
  int id = (int) v;
  int i, local_c;

  for (i = 0; i < 2; i++) {
    sleep(random() % 3);
    printf("Thread %d atingiu a barreira.\n", id);
    local_c = __sync_add_and_fetch (&c, 1);
    if (local_c == N) { 
      roleta_saida = 0;
      roleta_entrada = 1;
      futex_wake(&roleta_entrada, N-1);
    }
    else
      futex_wait(&roleta_entrada, 0);

    printf("Thread %d passou pela roleta de entrada.\n", id);

    local_c = __sync_sub_and_fetch (&c, 1);
    if (local_c == 0) { 
      roleta_entrada = 0;
      roleta_saida = 0;
      futex_wake(&roleta_saida, N-1);
    }
    else
      futex_wait(&roleta_saida, 0);
    printf("Thread %d passou pela roleta de saída.\n", id);
  }
  return NULL;
}

int main() {
  pthread_t thr[N];
  int i = 0;

  srandom(time(NULL));
  for (i = 0; i < N; i++) 
    pthread_create(&thr[i], NULL, f_thread, (void*) i);

  pthread_exit(NULL);
}


