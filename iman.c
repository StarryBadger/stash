#include "headers.h"
int resolveHost(char *hostname, char *ip)
{
    struct hostent *hostInfo;
    struct in_addr **addressList;
    int i;
    hostInfo = gethostbyname(hostname);
    if (hostInfo == NULL)
    {
        fprintf(stderr, "\x1b[31mUnable to resolve host\n\x1b[0m");
        return 1;
    }
    addressList = hostInfo->h_addr_list;
    for (i = 0; addressList[i] != NULL; i++)
    {
        strcpy(ip, inet_ntoa(*addressList[i]));
        return 0;
    }
    fprintf(stderr, "\x1b[31mUnable to resolve host\n\x1b[0m");
    return 1;
}
void iman(command cmd)
{

}