#include "headers.h"
void warp(char *input, char *home, char *prevPath)
{
    char beforeWarp[PATH_MAX];
    char current[PATH_MAX];
    getcwd(beforeWarp, PATH_MAX);
    char *paths = removeSubstring("warp", input);
    char *path = strtok(paths, " \n\t");
    if (path == NULL)
    {
        chdir(home);
        printf("%s\n", home);
    }
    while (path != NULL)
    {
        printf("PATH:%s\n", path);
        mystrcpy(current, path);
        if (prefix("~", path))
            mystrcpy(current, replaceTildeWithHome(home, path));
        if (equal("-", path) && prevPath)
            mystrcpy(current, prevPath);
        chdir(current);
        getcwd(current, PATH_MAX);
        printf("%s\n", current);
        path = strtok(NULL, " \n\t");
    }
    mystrcpy(prevPath, beforeWarp);
}