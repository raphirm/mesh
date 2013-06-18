#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen

#include <unistd.h>      // getopt
#include "conn_server.h"
#include "conn_io.h"     // send_all
#include "main.h"
#include "new.h"
#include "broadcast.h"



void parse(int connection_fd, struct nodelist *noderoot)
{
	struct paket message; /* we expect some line of text shorter than 132 chars */

	if(read_line(connection_fd, &message, 132)->content == NULL ) 
	{
		perror("Couldn't read a line of text");
	}
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

		message.paketType = 'O';
		send_all(connection_fd, &message, sizeof(message));
	}
	printf("\n\n\n");
}
