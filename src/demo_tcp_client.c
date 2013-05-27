#include <stdio.h>
#include <stdlib.h>       // exit
#include <string.h>       // memset, memcpy, strlen
#include <unistd.h>       // getopt
#include "conn_client.h"  // open_connection_to
#include "conn_io.h"      // read_line

void recv_message( int sockfd) {
  char message[6]; /* we expect "Hello" */
  message[5] = '\0';

  if( read(sockfd, message, 5) != 5 ) {
    perror("Couldn't read 5 chars");
  }
  else {
    printf("Message from server: %s\n", message);
  }

}

void read_one_line( int sockfd) {
  char message[60]; /* we expect some line of text shorter than 59 chars */

  if( read_line(sockfd, message, 60) == NULL ) {
    perror("Couldn't read a line of text");
  }
  else {
    printf("Text line from server: %s", message);
  }

}

void report_error2( char* message ) {
  fprintf( stderr, "ERROR: %s\n", message );
}

void usage() {
  printf("Usage: demo_tcp_client hostname port\n");
}

int maidddn(int argc, char *argv[])
{
    int sockfd;

    if (argc < 3) {
       usage();
       exit(0);
    }

    if( (sockfd = open_connection_to( argv[1], atoi(argv[2]))) == 0) {
      report_error( "couldn't open connection to destination" );
      return -1;
    }

    recv_message( sockfd );
    read_one_line( sockfd );

    disconnect_server( sockfd );
    return 0;
}
