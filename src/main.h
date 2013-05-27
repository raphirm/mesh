// Roles that a node can play
#define HOP    0
#define ZIEL   1
#define QUELLE 2
#define NO_TCP_PORT -1

typedef struct  {
 short paketID;
 char target;
 char paketType;
 char content[127];
} paket ;