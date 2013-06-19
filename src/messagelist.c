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
#include "messagelist.h"
#include <stdio.h>
#include <stdlib.h>

int llist_init (llist_t *llistp) 
{
  int rtn;

  llistp->first = NULL;
  if ((rtn = pthread_mutex_init(&(llistp->mutex), NULL)) !=0)
    fprintf(stderr, "pthread_mutex_init error %d",rtn), exit(1);
  return 0;
}

int llist_insert_data (index_t index, void *datap, llist_t *llistp) 
{
  llist_node_t *cur, *prev, *new;
  int found = 0;

  pthread_mutex_lock(&(llistp->mutex));

  for (cur=prev=llistp->first; cur != NULL; prev=cur, cur=cur->nextp) {
    if (cur->index.socket == index.socket && cur->index.messageid == index.messageid) {
      free(cur->datap);
      cur->datap = datap;
      found= 1;
      break;
    }
  }
  if (!found) {
    new = (llist_node_t *)malloc(sizeof(llist_node_t));
    new->index = index;
    new->datap = datap;
    new->nextp = cur;
    if (cur==llistp->first)
      llistp->first = new;
    else
      prev->nextp = new;
  }

  pthread_mutex_unlock(&(llistp->mutex));

  return 0;
}
int llist_remove_data(index_t index, void **datapp, llist_t *llistp) 
{
  llist_node_t *cur, *prev;

  /* Initialize to "not found" */
  *datapp = NULL;

  pthread_mutex_lock(&(llistp->mutex));

  for (cur=prev=llistp->first; cur != NULL; prev=cur, cur=cur->nextp) {
    if (cur->index.socket == index.socket && cur->index.messageid == index.messageid) {
      *datapp = cur->datap;
      prev->nextp = cur->nextp;
      free(cur);
      break;
    }
  }

  pthread_mutex_unlock(&(llistp->mutex));

  return 0;
}
int llist_find_data(index_t index, void **datapp, llist_t *llistp) 
{
  llist_node_t *cur, *prev;

  /* Initialize to "not found" */
  *datapp = NULL;

  pthread_mutex_lock(&(llistp->mutex));

  /* Look through index for our entry */
  for (cur=prev=llistp->first; cur != NULL; prev=cur, cur=cur->nextp) {
    if (cur->index.socket == index.socket && cur->index.messageid == index.messageid) {
      *datapp = cur->datap; 
      break;
    }
  }

  pthread_mutex_unlock(&(llistp->mutex));

  return 0;
}
int llist_change_data(index_t index, void *datap, llist_t *llistp)
{
  llist_node_t *cur, *prev;
  int status = -1; /* assume failure */

  pthread_mutex_lock(&(llistp->mutex));

  for (cur=prev=llistp->first; cur != NULL; prev=cur, cur=cur->nextp) {
    if (cur->index.socket == index.socket && cur->index.messageid == index.messageid) {
      cur->datap = datap;
      prev->nextp = cur->nextp;
      free(cur);
      status = 0;
      break;
    }

  }

  pthread_mutex_unlock(&(llistp->mutex));

  return status;
}
int llist_show(llist_t *llistp)
{
  llist_node_t *cur;

  pthread_mutex_lock(&(llistp->mutex));

  printf (" Linked list contains : \n");
  for (cur=llistp->first; cur != NULL; cur=cur->nextp) {
    printf ("Index: %d\tData: %s \n", cur->index, cur->datap);    
  }

  pthread_mutex_unlock(&(llistp->mutex));

  return 0;
}
