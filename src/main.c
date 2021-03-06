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
#include <pthread.h>
#include "messagelist.h"


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
	struct route *routes;
	routes = malloc(sizeof(struct route));
	routes->zielt = NULL;
	routes->quellet = NULL;
	                

	
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
		
			//parse(connection_fd, noderoot, pkgroot, routes, node_role);
		}
		else {
			report_error("failed to get a client connection");
		}
		disconnect_client( sock_fd);
	}
	return 0; 
}