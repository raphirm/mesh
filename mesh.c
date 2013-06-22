/* A simple node: 
*
* Description: 
*
*  rule:
*    all received paket are send to all ports except the once it received the paket from
*
*
* Author: Detlev Ziereisen (C) 2013, zhaw@ziereisen.ch
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
#include "mesh.h"        // 


void report_error( char* message ) {
  fprintf( stderr, "ERROR: %s\n", message );
}

// Roles that a node can play
short node_role = HOP;
int   tcp_port  = NO_TCP_PORT;

void parse_options( int argc, char *argv[])
{
  char optchar;

  while( ( optchar = getopt( argc, argv, "-hqz" ) ) != -1 ) {
    switch( optchar ) {
      case 1: // optchar '-' will assign non-option to 1
        tcp_port = atoi(optarg);
        break;
      case 'n': 
	createNewThread(argv);
	break;
      case 'z':
      case 'q':
      case '?':
      default:
	if (tcp_port == NO_TCP_PORT ) {
          printf("Usage: server port [-n port]\n(-z-q is not supported)\n");
          exit( 0 );
	}
    }
  }

  if (tcp_port == NO_TCP_PORT ) {
    report_error("no port provided");
    exit( -1);
  }
}


paket getpaket() {
  paket *p= malloc (sizeof(paket));
  if(p==0) FatalError("Error: Unable to allocate more memory.");

  return *p;
}


paket getpaketID(int id) {
  paket *p= malloc (sizeof(paket));
  if(p==0) FatalError("Error: Unable to allocate more memory.");

    
  p.paketID=id;
  return *p;
}


int main(int argc, char *argv[])
{
  int sock_fd, connection_fd;
  pthread_t pthread;
  extern int optind;                // from unistd.h:getopt

  paket pak= getpaketID(6);

  parse_options( argc, argv );

  if( (sock_fd = listen_on_port(tcp_port) ) < 0 ) {
    report_error("failed to listen on the port");
    return sock_fd;
  }

  if( (connection_fd = connect_with_client( sock_fd )) != 0) {
      paket pak2= getpaket();

    send_all(connection_fd, "Hello\n",         strlen("Hello\n"));
    send_all(connection_fd, "Hello Goodbye\n", strlen("Hello Goodbye\n"));
  }
  else {
    report_error("failed to get a client connection");
  }
  disconnect_client( sock_fd);

  return 0; 
}
