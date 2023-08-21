#include "headers.h"

void prompt()
{
    char *username = getlogin();
    char hostname[1000];
    char path[100];
    getcwd(path, sizeof(path));
    gethostname(hostname, sizeof(hostname));
    if (prefix(home, path))
    {
        printf("<%s@%s:%s>", username, hostname, replaceHomeWithTilde(path));
    }
    else
        printf("<%s@%s:%s>", username, hostname, path);
}
