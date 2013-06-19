#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen

#include <unistd.h>      // getopt
#include "conn_server.h"
#include "conn_io.h"     // send_all
#include "main.h"
#include "new.h"
#include "broadcast.h"
#include "pkglist.h"


void parse(int connection_fd, struct nodelist *noderoot, struct pkglist *pkgroot, struct route *routes, short node_role)
{
	struct paket message; /* we expect some line of text shorter than 132 chars */

	while(fgets(&message, 132, read_line(connection_fd)) != NULL ) 
	{
		
	int i;
	for (i = 0; i < sizeof(message.content); i++)
	{
		if (i > 0) 
		{
			printf(":");
		}
		else
		{
			printf("Content:");
		}
		printf("%02X", message.content[i]);

	}
	printf("\n");
	printf("paketID: %i\n", ntohs(message.paketID));
	printf("Target: %u\n", (unsigned int)message.target);
	printf("PaketType: %c\n", message.paketType);
	if(message.paketType == 'N'){

		unsigned char ip[4] = {message.content[0], message.content[1], message.content[2], message.content[3]};
		unsigned short prt = (unsigned short) (message.content[4]<<8)|message.content[5];
		node_add(noderoot, ip, prt);
		node_list(noderoot);
		node_search(noderoot, ip, prt);
	}

	if(message.paketType == 'C'){
		struct pkglist *node = pkg_search (pkgroot, message.paketID, (unsigned int) message.target);
		if(node == NULL){
			printf("Neues Packet empfangen mit ID %i, route vorhanden?\n", ntohs(message.paketID));
			
			node = pkg_add (pkgroot, message.paketID, message.target);
			if((message.target == 1 && node_role == ZIEL) || (message.target == 0 && node_role == QUELLE)){
				printf("Am Ziel angekommen! Sende antwort!\n");
				message.paketType = 'O';
				send_all(connection_fd, &message, sizeof(message));
			}
			else if((message.target == 1 && routes->zielt != NULL) ||(message.target ==0 && routes->quellet != NULL)){
				printf("Route schon vorhanden\n");
			}else{
				printf("keine Route vorhanden, broadcaste in das Netzwerk!\n");
				processForBroadcast (noderoot, node, message, routes);
			}

		}else{
			printf("Packet mit id %i schon gesehen, verwerfen!\n",  ntohs(message.paketID));

		}
		
		
	}
	printf("\n\n\n");
	}
}
