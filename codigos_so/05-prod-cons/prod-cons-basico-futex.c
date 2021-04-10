/*
 * Código para produtor e consumidor com controle de 
 * concorrência baseado em operações atômicas e futex.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/futex.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define N_ITENS 10
int buffer[N_ITENS];

int inicio = 0, final = 0, cont = 0;

/* Retorna -1 se o futex não bloqueou e 
            0 caso contrário */
int futex_wait(void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, 
                 val1, NULL, NULL, 0);
}

/* Retorna o número de threads que foram acordadas */
int futex_wake(void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, 
                   n, NULL, NULL, 0);
}

void* produtor(void *v) {
  int i;

  for (i = 0; i < 3 * N_ITENS; i++) {
    if (cont == N_ITENS) 
      futex_wait(&cont, N_ITENS);
    printf("Produtor, item = %d.\n", i);     
    final = (final + 1) % N_ITENS;
    buffer[final] = i;
    __sync_fetch_and_add(&cont, 1);
    if (cont == 1)
      futex_wake(&cont, 1);
    sleep(random() % 3);   /* Permite que a outra thread execute */
  }
  return NULL;
}

void* consumidor(void *v) {
  int i, aux;

  for (i = 0; i < 3 * N_ITENS; i++) {
    if (cont == 0) 
      futex_wait (&cont, 0);
    inicio = (inicio + 1) % N_ITENS;
    aux = buffer[inicio]; /* Item é consumido */
    printf("Consumidor, item = %d.\n", aux);
    if (aux < i)
      printf("Erro: item foi consumido antes de ser produzido.\n");
    else if (aux > i)      
      printf("Erro: item foi produzido antes de a posição estar livre.\n");
    __sync_fetch_and_add(&cont, -1);
    if (cont == N_ITENS -1)
      futex_wake(&cont, 1);
    sleep(random() % 3);  /* Permite que a outra thread execute */  
  }
  return NULL;
}

int main() {
  int i;
  
  pthread_t thr_produtor, thr_consumidor;

  /* Limpa o buffer */
  for (i = 0; i < N_ITENS; i++)
    buffer[i] = 0;
  
  pthread_create(&thr_produtor, NULL, produtor, NULL);
  pthread_create(&thr_consumidor, NULL, consumidor, NULL);

  pthread_join(thr_produtor, NULL); 
  pthread_join(thr_consumidor, NULL);

  return 0;
}

