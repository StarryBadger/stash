#include "headers.h"
char *homePath()
{
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    char *path = malloc(sizeof(char) * (length(cwd + 1)));
    mystrcpy(path, cwd);
    return path;
}
void prompt(char *home)
{
    char *username = getlogin();
    char hostname[1000];
    char path[100];
    getcwd(path, sizeof(path));
    gethostname(hostname, sizeof(hostname));
    if (prefix(home, path))
    {
        printf("<%s@%s:%s>", username, hostname, replaceHomeWithTilde(home, path));
    }
    else
        printf("<%s@%s:%s>", username, hostname, path);
}
