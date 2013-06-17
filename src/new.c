#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen
#include "main.h"

void node_add(struct nodelist *root, unsigned char ip[4], unsigned short port)
{	
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
	unsigned char ipnew[4] = { ip[0], ip[1], ip[2], ip[3] };
	bef->ip = ipnew;
	bef->port = port;
	bef->next = NULL;
	return;
}
void print_list(struct nodelist *root){
	struct nodelist *conductor = root;
	while ( conductor != NULL ) {
    	printf( "%hu\n", conductor->port );
    	conductor = conductor->next;
	}
}
