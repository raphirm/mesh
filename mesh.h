
typedef struct  {
 short paketID;
 char target;
 char paketType;
 char content[127];
} paket ;

#define HOP    0
#define ZIEL   1
#define QUELLE 2
#define NO_TCP_PORT -1

#define FatalError(Str)   fprintf(stderr, "%s\n", Str), exit(1)  // http://www.iDevelopment.info



