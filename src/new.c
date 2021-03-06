#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen
#include "main.h"
#include <stdbool.h>
#include <pthread.h>


void node_remove(struct nodelist *root, unsigned char ip[4], unsigned short port)
{	
	unsigned char tarip[4] = { ip[0], ip[1], ip[2], ip[3] };
	struct nodelist *bef = root;
	struct nodelist *del;
	struct nodelist *aft;
	if(root->next == NULL){
		perror("Nothing to delete \n");
	}
	del = bef->next;
	bool endReached = false;
	while(del->port != port ||strcmp(del->ip, tarip) == 0   )
	{
		bef = bef->next; 
		del = bef->next;
		if ( del->next == NULL)
		{
			endReached = true;
			break;
		}

	}
	if(endReached){
		perror("Nothing to delte\n");
		return;
	}
	else{
		aft = del->next;
		bef->next = aft;
		free(del);
	
	}
	


}
struct nodelist *node_search(struct nodelist *root, unsigned char ip[4], unsigned short port)
{	
	unsigned char ips[4] = { ip[0], ip[1], ip[2], ip[3] } ; 

	struct nodelist *find = root->next;
	struct nodelist *result = NULL;
	while(find!=NULL){

		if(strcmp(find->ip, ips) == 0 && find->port == port){
			result = find;
			printf("FOUND!!\n");
			return result;
			break;
		}
		find = find->next;
	}
	if(find == NULL){
		return find;
	}
}
void node_list(struct nodelist *root){
	struct nodelist *conductor = root;
	while ( conductor != NULL ) {
    	printf( "%hu\n", conductor->port );
		printf( "%i.%i.%i.%i\n", conductor->ip[0], conductor->ip[1], conductor->ip[2], conductor->ip[3]);
    	conductor = conductor->next;
	}
}
void node_add(struct nodelist *root,int socket, pthread_t *sock, struct bufmsg *buffer )
{	
	if(node_search (root, ip, port) == NULL){
	
	struct nodelist *bef = root;
	while(bef->next != NULL){
			bef = bef->next;
	}
	bef->next = malloc( sizeof(struct nodelist));
	bef = bef->next;
	if(bef == 0)
	{
		printf("out of memory");
		return 0;
	}

	bef->ip[0] = ip[0];
	bef->ip[1] = ip[1];
	bef->ip[2] = ip[2];
	bef->ip[3] = ip[3];
	bef->port = port;
	bef->next = NULL;
	return;
	}
	else{
		printf("Node Already added\n");
	}
}

