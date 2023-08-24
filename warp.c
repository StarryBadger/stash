#include "headers.h"
bool OLDPWD = false;
char prevPath[PATH_MAX] = "\0";
void warp(command input)
{
    char beforeWarp[PATH_MAX];
    char current[PATH_MAX];
    if (input.argc == 1)
    {
        chdir(home);
        printf("%s\n", home);
        OLDPWD=true;
    }
    for (int i = 1; i < input.argc; i++)
    {
        getcwd(beforeWarp, PATH_MAX);
        mystrcpy(current, input.argv[i]);
        if (prefix("~", current))
            mystrcpy(current, replaceTildeWithHome(current));
        if (equal("-", current) && prevPath != "\0")
        {
            if (OLDPWD)
                mystrcpy(current, prevPath);
            else
                fprintf(stderr, "warp: OLDPWD not set\n");
        }
        else
        {
            OLDPWD = true;
        }
        chdir(current);
        getcwd(current, PATH_MAX);
        mystrcpy(prevPath, beforeWarp);
        printf("%s\n", home);
    }
}