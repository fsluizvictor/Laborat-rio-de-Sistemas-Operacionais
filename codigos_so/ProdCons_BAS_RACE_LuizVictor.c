/*
 * Código para produtor e consumidor com uma tentativa de
 * controle de concorrência baseada em espera ocupada.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_ITENS 10
int buffer[N_ITENS]; //Define a quantidade de itens no buffer

int inicio = 0, final = 0, cont = 0; //Inicia as variáveis

void* produtor(void *v) {//Inicia a função do produtor	
  int i,aux;		

  for (i = 0; i < 3 * N_ITENS; i++) { //criação de itens
    while (cont == N_ITENS) ;	//Enquanto o contador for igual ao numero de itens
    printf("Produtor, item = %d.\n", i);     //printa o item produzido
    final = (final + 1) % N_ITENS;	// o coloca no final do 
    buffer[final] = i;//adiciona o item ao final
    aux = cont;  
    sleep(random() % 3);   /* Permite que a outra thread execute */
    cont = aux + 1;
  }
  printf("Produção encerrada.\n");   //encerra  a  produção quando alcançar o numero de itens  
  return NULL;
}

void* consumidor(void *v) { //inicia a função do consumidor
  int i, aux;	

  for (i = 0; i < 3 * N_ITENS; i++) { //Vai até o numero 30 de itens consumidor
    while (cont == 0) ;
    inicio = (inicio + 1) % N_ITENS; //Aponta para o inicio do buffer
    aux = buffer[inicio]; /* Item é consumido */
    printf("Consumidor, item = %d.\n", aux); //Anuncia o item que consumiu
    if (aux < i) //Controle de bugs
      printf("Erro: item foi consumido antes de ser produzido.\n");
    else if (aux > i)      
      printf("Erro: item foi produzido antes de a posição estar livre.\n");
    aux = cont; 
    sleep(random() % 3);  /* Permite que a outra thread execute */  
    cont = aux - 1; 
  }//Encerra o consumo quando os itens forem consumidos
  printf("Consumo encerrado.\n");     
  return NULL;
}

int main() {
  int i;
  
  pthread_t thr_produtor, thr_consumidor; //Cria a thread 

  printf("Desenvolvido por Luiz Victor");

  /* Limpa o buffer */
  for (i = 0; i < N_ITENS; i++) // Inicia o processo 
    buffer[i] = 0;
  
  pthread_create(&thr_produtor, NULL, produtor, NULL);//Chama a thread do produtor
  pthread_create(&thr_consumidor, NULL, consumidor, NULL);//Chama a thread do consumidor

  pthread_join(thr_produtor, NULL);  //Une as threads e sincroniza com a main
  pthread_join(thr_consumidor, NULL);

  return 0;
}
