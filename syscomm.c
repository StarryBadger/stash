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
    int child = fork();
    if (child > 0)
    {
        if (cmd.foreground)
        {
            int status=waitForMe(child);
            if (WIFSTOPPED(status))
            {
                insertNode(bglist, cmd.argv[0], child);
            }
        }
        else
        {
            printf("%d\n", child);
            insertNode(bglist, argv[0], child);
        }
    }
    else if (child == 0)
    {
        setpgid(0, 0);
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        if (execvp(argv[0], argv) == -1)
        {
            fprintf(stderr, "\x1b[31mERROR : '%s' is not a valid command\n\x1b[0m", argv[0]);
            exit(1);
        }
    }
    else
    {
        perror("fork");
        return;
    }
}