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
        printf("<\x1b[32m%s@%s\x1b[0m:\x1b[34m%s %s:%ds\x1b[0m> ", username, hostname, path,timetaker,timetakertime);
    }
    else
    {
        printf("<\x1b[32m%s@%s\x1b[0m:\x1b[34m%s\x1b[0m> ", username, hostname, path);
    }
}
