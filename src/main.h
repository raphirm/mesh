// Roles that a node can play
#define HOP    0
#define ZIEL   1
#define QUELLE 2
#define NO_TCP_PORT -1
#define MSIZE 132

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

struct nodelist
{
	unsigned char ip;
	unsigned short port;
	struct nodelist *next;
};