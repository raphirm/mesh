// Roles that a node can play
#define HOP    0
#define ZIEL   1
#define QUELLE 2
#define NO_TCP_PORT -1
#define MSIZE 132
#define MAX_BUF_SIZE 100
#define PACKAGE_LIST_MAX_ITEMS=128;

struct  paket
{
 unsigned short paketID;
 unsigned char	 target;
 char paketType;
 unsigned char content[128];
};
struct newp
{
 unsigned char ip[4];
 unsigned short port;
 char cont[122];
};



struct route
{
	llist_node_t *zielt;
	llist_node_t *quellet;
};


struct pkgListItem {
	unsigned short id;
	unsigned short pid;
	int sourceSocket;
};

struct threadinfos
{
	llist_t *nodes;
	llist_node_t *me;
	struct pkgListItem *packages;
	struct route *routes;
};
