#include "headers.h"
void sysexec(command *cmd)
{
    printf("%d\n",cmd->argc);
    for (int i = 0; i < cmd->argc; i++)
    {
        printf("%s\n", cmd->argv[i]);
    }
    if (cmd->foreground)
    {
        int child = fork();
        if (child > 0)
        {
            int status;
            waitpid(child, &status, 0);
        }
        else if (child == 0)
        {
            execvp(cmd->argv[0], cmd->argv);
        }
        else
        {
            // error handling
            //  perror("fork");
        }
    }
    else
    {
        
    }
}