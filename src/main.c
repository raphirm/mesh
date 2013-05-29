/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) rm 2013 <raphael@marques.com>
 * 
 * mesh is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * mesh is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen

#include <unistd.h>      // getopt
#include "conn_server.h"
#include "conn_io.h"     // send_all
#include "main.h"

short node_role = HOP;

int   tcp_port  = NO_TCP_PORT;
void report_error( char* message ) {
  fprintf( stderr, "ERROR: %s\n", message );
}
void parse_options( int argc, char *argv[])
{
  char optchar;

  while( ( optchar = getopt( argc, argv, "-hqz" ) ) != -1 ) {
    switch( optchar ) {
      case 'z':
        node_role = ZIEL;
        break;;
      case 'q':
        node_role = QUELLE;
        break;;
      case 1: // optchar '-' will assign non-option to 1
        tcp_port = atoi(optarg);
        break;

      case 'h':
      case '?':
      default:
	if (tcp_port == NO_TCP_PORT ) {
          printf("Usage: server port [-z|-q]\n");
          exit( 0 );
	}
    }
  }

  if (tcp_port == NO_TCP_PORT ) {
    report_error("no port provided");
    exit( -1);
  }
}


int main(int argc, char *argv[])
{

 int sock_fd, connection_fd;
 pthread_t pthread;
 extern int optind;                // from unistd.h:getopt

 parse_options( argc, argv );
 while (1)
 {
  if( (sock_fd = listen_on_port(tcp_port) ) < 0 ) {
   report_error("failed to listen on the port");
   return sock_fd;
  }

  if( (connection_fd = connect_with_client( sock_fd )) != 0) {
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
	char con[122];
	for (i = 6; i < 128; i++){
		con[i-5] = message.content[i];
	}
    struct newp newinfo = {{*ip},{prt},{*con}};		  
    printf("NewIP: %i.%i.%i.%i\n", newinfo.ip[0], newinfo.ip[1], newinfo.ip[2], newinfo.ip[3]);
    printf("NewPort: %i\n", newinfo.port);
	printf("NewContent: %s\n", newinfo.cont);
	int i;
	for (i = 0; i < sizeof(newinfo.cont); i++)
    {
     if (i > 0) 
     {
      printf(":");
     }
     else
     {
      printf("NewMsgContent:");
     }
     printf("%02X", newinfo.cont[i]);

    }
	printf("\n");
   }
   if(message.paketType == 'C'){
    message.paketType = 'O';
    send_all(connection_fd, &message, sizeof(message));
   }

  }
  else {
   report_error("failed to get a client connection");
  }
  disconnect_client( sock_fd);
 }
return 0; 
}