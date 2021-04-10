/*
 * Implementa��o sujeita a deadlock do 
 * problema do jantar dos fil�sofos.

 * Sem controle da exibi��o dos estados, para
 * ilustrar interfer�ncia.
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
enum pos_garfo {ESQ, MESA, DIR} pos_garfo[N];
char mesa[4*N+1];

/*
 *  garfo esq = phil_id
 *  garfo dir = (phil_id + 1) % N
 */

void print() {
  printf("%s%c%c\n", &mesa[1], mesa[0], mesa[1]);
}

void fica_com_fome(int phil_id) {
  mesa[4 * phil_id + 3] = 'H';
  print();
  sleep(1);
}

void come(int phil_id) {
  mesa[4 * phil_id + 3] = 'E';
  print();
  sleep(1);
}

void pega_garfo_esq(int phil_id) {
  sem_wait(&sem_garfo[phil_id]);
  mesa[4 * phil_id] = ' ';
  mesa[4 * phil_id + 1] = ' ';
  mesa[4 * phil_id + 2] = '|';
  print();
  /* sleep(1); */
}  

void pega_garfo_dir(int phil_id) {
  int dir = (phil_id + 1) % N;
  sem_wait(&sem_garfo[dir]);
  mesa[4 * dir] = '|';
  sleep(1);
  mesa[4 * dir + 1] = ' ';
  mesa[4 * dir + 2] = ' ';
  print();
  /* sleep(1); */ 
}

void solta_garfos_pensa(int phil_id) {
  int dir = (phil_id + 1) % N;
  sem_post(&sem_garfo[dir]);
  sem_post(&sem_garfo[phil_id]);
  mesa[4 * phil_id] = ' ';
  mesa[4 * phil_id + 1] = '-';
  mesa[4 * phil_id + 2] = ' ';
  mesa[4 * dir] = ' ';
  mesa[4 * dir + 1] = '-';
  mesa[4 * dir + 2] = ' ';
  mesa[4 * phil_id + 3] = 'T';
  print();
  sleep(1);
}


void* f_phil(void *v) {
  int phil_id = *(int *) v;
  int i;


  for (i = 0; i < N_CICLOS; i++) {
    fica_com_fome(phil_id);
    
    pega_garfo_dir(phil_id);
    pega_garfo_esq(phil_id);

    come(phil_id);
	
    solta_garfos_pensa(phil_id);
  }
  
  return NULL;
}

int main() {
  pthread_t thr[N];
  int i, phil_id[N];

  for (i = 0; i < N; i++) {
      sem_init(&sem_garfo[i], 0, 1);
      pos_garfo[i] = MESA;
      mesa[4 * i] = ' ';
      mesa[4 * i + 1] = '-';
      mesa[4 * i + 2] = ' ';
      mesa[4 * i + 3] = 'T';
  }
  
  mesa[4*N+1] = 0;

  for (i = 0; i < N; i++) {
    phil_id[i] = i;
    pthread_create(&thr[i], NULL, f_phil, (void*) &phil_id[i]);
  }

  for (i = 0; i < N; i++) 
    pthread_join(thr[i], NULL);

  for (i = 0; i < N; i++) 
    sem_destroy(&sem_garfo[i]);
    
  return 0;
}
