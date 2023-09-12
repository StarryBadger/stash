#ifndef __IMAN_H
#define __IMAN_H
#define PORT 80
#define HOSTNAME "man.he.net"
#define MAX_RESPONSE 750
int resolveHost(char *ip);
void iman(command cmd);
void printWithoutTags(char*);
#endif