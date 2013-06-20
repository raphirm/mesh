/********************************************************
 * An example source module to accompany...
 *
 * "Using POSIX Threads: Programming with Pthreads"
 *     by Brad nichols, Dick Buttlar, Jackie Farrell
 *     O'Reilly & Associates, Inc.
 *
 ********************************************************
 * llist_threads.h --
 *
 * Include file for linked list with threads support
 */
#include <pthread.h>



typedef struct llist_node {
	int socket;
	thread_t thread;	
  struct bufmsg *buffer;
  struct llist_node *nextp;
} llist_node_t;

typedef struct llist { 
  llist_node_t *first;
  pthread_mutex_t mutex;
} llist_t;

int llist_init (llist_t *llistp);
int llist_insert_data (index_t index, void *datap, llist_t *llistp);
int llist_remove_data(index_t index, void **datapp, llist_t *llistp);
int llist_find_data(index_t index, void **datapp, llist_t *llistp);
int llist_change_data(index_t index, void *datap, llist_t *llistp);
int llist_show(llist_t *llistp);