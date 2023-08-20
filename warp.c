#include "headers.h"
void warp(char *input, char *home, char *prevPath)
{
    char s[100];
    mystrcpy(prevPath, getcwd(s, 100));
    char *paths = removeSubstring("warp", input);
    char *path = strtok(paths, " \n\t");
    if (path == NULL)
    {
        chdir(home);
        mystrcpy(prevPath, getcwd(s, 100));
        printf("%s\n", home);
    }
    while (path != NULL)
    {
        // printf("\nThe previous path was %s\n\n", prevPath);
        if (prefix("~", path))
            mystrcpy(path, replaceTildeWithHome(home, path));
        if (equal("-", path))
            mystrcpy(path, prevPath);
        chdir(path);
        printf("%s\n", getcwd(s, 100));
        path = strtok(NULL, " \n\t");
    }
}