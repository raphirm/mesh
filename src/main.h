// Roles that a node can play
#define HOP    0
#define ZIEL   1
#define QUELLE 2
#define NO_TCP_PORT -1
#define MSIZE 132

typedef struct  {
 unsigned short paketID;
 unsigned char	 target;
 char paketType;
 char content[128];
} packet ;