#ifndef __iMan_H
#define __iMan_H
#define PORT 80
#define HOSTNAME "man.he.net"
#define MAX_RESPONSE 750
int resolveHost(char *ip);
void iMan(command cmd);
void printWithoutTags(char*);
#endif