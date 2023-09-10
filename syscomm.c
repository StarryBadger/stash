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
            if (execvp(argv[0], argv) == -1)
                fprintf(stderr, "\x1b[31mUnable to execute %s\n\x1b[0m", argv[0]);
        }
        else
        {
            perror("fork");
            return;
        }
    }
    else
    {
        int child = fork();
        if (child > 0)
        {
            printf("%d\n", child);
            insertNode(bglist, argv[0], child, true);
        }
        else if (child == 0)
        {
            if (execvp(argv[0], argv) == -1)
                fprintf(stderr, "\x1b[31mUnable to execute %s\n\x1b[0m", argv[0]);
        }
        else
        {
            perror("fork");
            return;
        }
    }
}