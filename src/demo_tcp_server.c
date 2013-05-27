/*
*  C Implementation: server
*
* Description: 
*
*
* Author: Tomas Pospisek <tpo_deb@sourcepole.ch>, (C) 2006
*
* Copyright: See COPYING file that comes with this distribution
*
*/
#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen
#include <unistd.h>      // getopt
#include "conn_server.h"
#include "conn_io.h"     // send_all

void report_error( char* message ) {
  fprintf( stderr, "ERROR: %s\n", message );
}

// Roles that a node can play
#define HOP    0
#define ZIEL   1
#define QUELLE 2
short node_role = HOP;

#define NO_TCP_PORT -1
int   tcp_port  = NO_TCP_PORT;

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
        break;;
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

int maiddfen(int argc, char *argv[])
{
  int sock_fd, connection_fd;
  pthread_t pthread;
  extern int optind;                // from unistd.h:getopt

  parse_options( argc, argv );

  if( (sock_fd = listen_on_port(tcp_port) ) < 0 ) {
    report_error("failed to listen on the port");
    return sock_fd;
  }

  if( (connection_fd = connect_with_client( sock_fd )) != 0) {
    send_all(connection_fd, "Hello\n",         strlen("Hello\n"));
    send_all(connection_fd, "Hello Goodbye\n", strlen("Hello Goodbye\n"));
  }
  else {
    report_error("failed to get a client connection");
  }
  disconnect_client( sock_fd);

  return 0; 
}
