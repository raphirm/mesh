#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen
#include <assert.h>
#include <unistd.h>      // getopt
#include "messagelist.h"
#include "main.h"
#include "conn_server.h"
#include "conn_io.h"     // send_all
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdbool.h>
#include "buffer.h"
//thread who is reachable for all others, to send data. It spawns a listener thread to recv data and parses it.

void *listenT(void *argument)
{
	int j = 0;
	struct threadinfos *ti;
	ti = (struct threadinfos *) argument;
	llist_node_t *me = ti->me;
	int socket = me->index;
	char *ca = malloc(2);
	struct bufmsg *buffer = me->datap;
 while(recv(socket, ca, 2, MSG_PEEK)>0){
	struct paket message; /* we expect some line of text shorter than 132 chars */
	while(fgets(&message, 132, read_line(socket)) != NULL ) 
	{
		if(message.paketType == 'C'){
				j = j + 1;
				printf("Am Ziel angekommen! Sende antwort! %i \n", j);
				buf_push(message, buffer);
				
				//message.paketType = 'O';
				//send_all(socket, &message, sizeof(message));
		}
	}
 }

pthread_mutex_lock(&buffer->mutex);
ti->me->alive=false;
pthread_cond_signal(&buffer->buff_empty);
pthread_mutex_unlock(&buffer->mutex);
pthread_exit(NULL);
}


//thread waits for work (looks to a buffer) and sends the packet over his socket. The buffer is directly reachable over the list "nodes".
void  startsthread(void *argument)
{
	
	struct threadinfos *ti;
	ti = (struct threadinfos *) argument;
	llist_node_t *me = ti->me;
	int socket = me->index;
	struct bufmsg *buffer = me->datap;
	pthread_t thread;
	struct route *routes = ti->routes;
	llist_t *nodes = ti->nodes;
	struct pkgListItem *packages =	ti->packages;
	int rt= pthread_create(&thread, NULL, (void*)&listenT ,(void *) ti);
	pthread_mutex_lock(&buffer->mutex);
	while(1){
		
		if(buffer->rd == buffer->wr && me->alive){
			pthread_cond_wait(&buffer->buff_empty, &buffer->mutex);
		}
		if(!me->alive)
		{
			free(buffer);
			me->index = socket;
			llist_remove_data (socket, nodes);
			pthread_mutex_unlock(&buffer->mutex);
			pthread_exit(NULL);
		}
		//mutex lock
		//buffer consumer/worker
		//mutex unlock
		struct paket *message;
		message = buf_pull(buffer);
		message->paketType = 'O';
		send_all(socket, message, sizeof(*message));

	}
	
	pthread_mutex_unlock(&buffer->mutex);
}

