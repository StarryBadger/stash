#include "headers.h"
void sysexec(command *cmd)
{
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
             perror("fork");
        }
    }
    else
    {

    }
}