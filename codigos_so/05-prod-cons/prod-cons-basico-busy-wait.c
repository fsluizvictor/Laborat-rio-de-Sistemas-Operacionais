/*
 * Código para produtor e consumidor com uma tentativa de
 * controle de concorrência baseada em espera ocupada.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_ITENS 10
int buffer[N_ITENS];

int inicio = 0, final = 0, cont = 0;

void* produtor(void *v) {
  int i;

  for (i = 0; i < 3 * N_ITENS; i++) {
    while (cont == N_ITENS) ;
    printf("Produtor, item = %d.\n", i);     
    final = (final + 1) % N_ITENS;
    buffer[final] = i;
    cont++;
    sleep(random() % 3);   /* Permite que a outra thread execute */
  }
  return NULL;
}

void* consumidor(void *v) {
  int i, aux;

  for (i = 0; i < 3 * N_ITENS; i++) {
    while (cont == 0) ;
    inicio = (inicio + 1) % N_ITENS;
    aux = buffer[inicio]; /* Item é consumido */
    printf("Consumidor, item = %d.\n", aux);
    if (aux < i)
      printf("Erro: item foi consumido antes de ser produzido.\n");
    else if (aux > i)      
      printf("Erro: item foi produzido antes de a posição estar livre.\n");
    cont--;
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

