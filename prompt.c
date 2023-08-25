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
        strcpy(path, replaceHomeWithTilde(path));
    }
    if (timetakertime > 2)
    {
        printf("<%s@%s:%s %s : %ds> ", username, hostname, path,timetaker,timetakertime);
    }
    else
    {
        printf("<%s@%s:%s> ", username, hostname, path);
    }
}
