#include "headers.h"
void sysexec(command cmd)
{
    char *argv[PATH_MAX + 1];
    for (int i = 0; i < cmd.argc; ++i)
    {
        argv[i] = malloc(sizeof(char) * (length(cmd.argv[i]) + 1));
        mystrcpy(argv[i], cmd.argv[i]);
    }
    argv[cmd.argc] = NULL;
    if (cmd.foreground)
    {
        int child = fork();
        if (child > 0)
        {
            int status;
            waitpid(child, &status, 0);
        }
        else if (child == 0)
        {
            execvp(argv[0], argv);
        }
        else
        {
            // error handling
            perror("fork");
        }
    }
    else
    {
        int child = fork();
        if (child > 0)
        {
            printf("%d\n", child);
            insertNode(bglist, argv[0], child);
        }
        else if (child == 0)
        {
            execvp(argv[0], argv);
        }
        else
        {
            perror("fork");
            // continue;
        }
        // execvp(command[0],command);
    }
}