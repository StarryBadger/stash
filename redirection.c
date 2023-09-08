#include "headers.h"
bool toRedirect(char *str)
{
    for (int i = 0; i < length(str); i++)
    {
        if (str[i] == '|' || str[i] == '<' || str[i] == '>')
            return true;
    }
    return false;
}
command redirection(command cmd)
{
    int pipers[128];
    char cmdStr[PATH_MAX];
    cmdStr[0] = '\0';
    for (int i = 0; i < cmd.argc; i++)
    {
        strcat(cmdStr, cmd.argv[i]);
        strcat(cmdStr, " ");
    }
    char *token = strtok(cmdStr, "|");
    int pipeCount = 0;
    while (token != NULL)
    {
        mystrcpy(pipers[pipeCount], token);
        pipeCount += 1;
        token = strtok(NULL, "|");
    }
    for (int i=0;i<pipeCount;++i)
    {
        
    }
}
