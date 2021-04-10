/*
 * Interface para locks recursivos.
 */

#include <pthread.h>

typedef struct {
  pthread_t thr;
  pthread_cond_t cond;  
  pthread_mutex_t lock_var;
  int c; 
} rec_mutex_t;

int rec_mutex_init(rec_mutex_t* rec_m);
int rec_mutex_lock(rec_mutex_t* rec_m);
int rec_mutex_unlock(rec_mutex_t* rec_m);
int rec_mutex_destroy(rec_mutex_t* rec_m);
