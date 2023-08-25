#include "headers.h"
bool OLDPWDWARP = false;
char prevPath[PATH_MAX] = "\0";
void warp(command input)
{
    char beforeWarp[PATH_MAX];
    char current[PATH_MAX];
    if (input.argc == 1)
    {
        chdir(home);
        printf("%s\n", home);
        OLDPWDWARP=true;
    }
    for (int i = 1; i < input.argc; i++)
    {
        getcwd(beforeWarp, PATH_MAX);
        mystrcpy(current, input.argv[i]);
        if (prefix("~", current))
            mystrcpy(current, replaceTildeWithHome(current));
        if (equal("-", current) && prevPath != "\0")
        {
            if (OLDPWDWARP)
                mystrcpy(current, prevPath);
            else
            {
                fprintf(stderr, "\x1b[31mwarp: OLDPWD not set\n\x1b[0m");
                return;
            }

        }
        else
        {
            OLDPWDWARP = true;
        }
        if (chdir(current)==-1)
        fprintf(stderr,"\x1b[31mwarp: No such file or directory\n\x1b[0m");
        return;
        getcwd(current, PATH_MAX);
        mystrcpy(prevPath, beforeWarp);
        printf("%s\n", current);
    }
}