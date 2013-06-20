#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen


#define PACKAGE_LIST_MAX_ITEMS=128;

pkgLstItem pkgList[PACKAGE_LIST_MAX_ITEMS];

/* Prüfe ob Paket bereits in Liste existiert 
 * true: Paket existiert bereits 
 * */
bool check(int connection_fd, struct paket *message)
{	
	int idx= calcIdx( message)
	return ( pkgList[idx]!=NULL); 
}

/* Mutex nicht notwendig, da sehr nah an atomarer Funktion */
void add (int connection_fd, struct paket *message){
	int idx= calcIdx( message);
    /* Mutex auf pkgList */
	pkgLstItem *itm= malloc(sizeof(struct pkgLstItem)); 
	itm.socket= connection_fd;
	itm.id= message.paketID;
	pkgList[idx]= itm;	
}

/* berechnet den Index im Array */
int calcIdx(struct paket *message){
	return message.paketID % PACKAGE_LIST_MAX_ITEMS;
}
	
	