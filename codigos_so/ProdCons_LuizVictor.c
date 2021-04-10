// SimulaÃ§Ã£o do problema dos produtores-consumidores
#include<stdio.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAXINTERACOES 20
#define MAXBUFFER 10

int buffer[MAXBUFFER];
int ultimo = 0; 
int primeiro  = 0;
int itens = 0;

void escreve(int valor) {
    buffer[ultimo] = valor;    /* escreve valor no buffer */
    ultimo = (ultimo + 1) % MAXBUFFER; /* incrementa Ã­ndice do primeiro livre */ }

int le() {
    int tmp;
    
    if (itens==0) /* ops. nenhum item disponivel */
       return -1; /* -1 Ã© um cÃ³digo de erro; os itens sao numeros positivos */
  
    tmp = buffer[primeiro];   /* recupera o valor do buffer */
    primeiro = (primeiro + 1) % MAXBUFFER;   /* incrementa o Ã­ndice do valor retirado */
    return tmp;
}

void *produtor1(void *arg) {
    int i;
    for (i = 0; i < MAXINTERACOES/2; i++) {  /* o produtor 1 vai inserir valores de 0 a MAX/2 */
        usleep( 1000.0 * (float)random()/RAND_MAX);  /* produtor dorme durante um tempo randÃ´mico entre 0 e 1000 micro-segundos*/ 
        itens++;
        escreve(i);                                      
    }
}

void *produtor2(void *arg) {
    int i;
    for (i = MAXINTERACOES/2; i < MAXINTERACOES; i++) { /* o produtor 2 vai inserir valores de MAX/2 a MAX */
        usleep( 1000.0 * (float)random()/RAND_MAX);  /* produtor dorme durante um tempo randÃ´mico entre 0 e 1000 micro-segundos*/ 
        itens++;  
        escreve(i);
    }
}

void *consumidor(void *arg) {
    int i, item;
    for (i = 0; i < MAXINTERACOES; i++) {
        item = le();
        if (item != -1)  {    /* -1 indica que nÃ£o havia nada no buffer */
           itens--;
           usleep( 3000.0 * (float)random()/RAND_MAX);  /* consumidor dorme durante um tempo randÃ´mico entre 0 e 1000 micro-segundos*/ 
           printf("\nConsumidor: %d - Itens restantes no buffer: %d", item, itens);
        }
        else {
           printf("\nConsumidor: sem item para consumir");
           i--; /* volta o contador de interacoes */
        }
    }
}


int main(int argc, char *argv[]) {
    int i;
    pthread_t pid1, pid2, cid; 

    printf("Desenvolvido por Luiz Victor");
 
    /* Cria threads */
    pthread_create(&pid1, NULL, produtor1, NULL); 
    pthread_create(&pid2, NULL, produtor2, NULL); 
    pthread_create(&cid, NULL, consumidor, NULL); 

    /* Aguarda o fim das threads */
    pthread_join(pid1, NULL); 
    pthread_join(pid2, NULL); 
    pthread_join(cid, NULL); 

    printf("\n\n");

    return 0;


}