#include "headers.h"
char *home;
char *homePath()
{
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    char *path = malloc(sizeof(char) * (length(cwd + 1)));
    mystrcpy(path, cwd);
    return path;
}
int main()
{
    home = homePath();
    readPastEventsFromFile(history, &historyCount);
    while (1)
    {
        prompt();
        char input[4096];
        fgets(input, 4096, stdin);
        execute(input);
    }
    free(home);
}
