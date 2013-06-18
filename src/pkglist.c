#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen
#include "main.h"
#include <stdbool.h>

struct pkglist *pkg_search(struct pkglist *pkgroot, unsigned short id , unsigned char target){

	struct pkglist *find = pkgroot->next;
	struct pkglist *result = NULL;
	while(find!=NULL){

		if(find->target == target && find->id == id){
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

void pkg_add(struct pkglist *pkgroot, unsigned short id , unsigned char target)
{
	if(pkg_search(pkgroot, id, target) == NULL){
	
		struct pkglist *bef = pkgroot;
		while(bef->next != NULL){
				bef = bef->next;
		}
		bef->next = malloc( sizeof(struct pkglist));
		bef = bef->next;
		if(bef == 0)
		{
			printf("out of memory");
			return 0;
		}

		bef->target = target;	
		bef->id = id;
		bef->next = NULL;
		return;
	}
	else{
		printf("Node Already added\n");
	}
}
void pkg_addNextHop(struct pkglist *pkg, struct nodelist *node)
{
	pkg->nexthop = node;
}

void pkg_remove(struct pkglist *pkgroot, unsigned short id , unsigned char target){
	struct pkglist *bef = pkgroot;
	struct pkglist *del;
	struct pkglist *aft;
	if(pkgroot->next == NULL){
		perror("Nothing to delete \n");
	}
	del = bef->next;
	bool endReached = false;
	while(del->target != target ||id != id   )
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

void pkg_list(struct pkglist *pkgroot) {
	struct pkglist *conductor = pkgroot;
	while ( conductor != NULL ) {
    	printf( "%hu\n", conductor->id );
		printf( "%c\n", conductor->target);
    	conductor = conductor->next;
	}
}