#include "headers.h"
bool toRedirectOrPipe(char *str)
{
    for (int i = 0; i < length(str); i++)
    {
        if (str[i] == '|' || str[i] == '<' || str[i] == '>')
            return true;
    }
    return false;
}
char toRedirect(char *str, char *strData1, char *strData2)
{
    for (int i = 0; i < length(str); i++)
    {
        strData1[i] = str[i];
        if (str[i] == '<')
        {
            strData1[i] = '\0';
            mystrcpy(strData2, str + i + 1);
            return 'R';
        }
        else if (str[i] == '>')
        {
            strData1[i] = '\0';
            if (i != (length(str) - 1) && str[i + 1] == '>')
            {
                mystrcpy(strData2, str + i + 2);
                return 'A';
            }
            else
            {
                mystrcpy(strData2, str + i + 1);
                return 'W';
            }
        }
    }
    return 'X';
}
void handlePipedExecution(int in, int out, command cmd)
{
    if (in != 0)
    {
        dup2(in, 0);
        close(in);
    }
    if (out != 1)
    {
        dup2(out, 1);
        close(out);
    }
    executeSingleCommand(cmd);
}
command redirection(command cmd)
{
    char pipers[32][128];
    char temp1[128], temp2[128];
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
    command pipes[pipeCount];
    char redirectInfo[pipeCount];
    char redirectHere[pipeCount][64];
    for (int i = 0; i < pipeCount; ++i)
    {
        bool foregroundFlag = true;
        if (i == pipeCount - 1)
        {
            foregroundFlag = cmd.foreground;
        }
        redirectInfo[i] = toRedirect(pipers[i], temp1, temp2);
        if (redirectInfo[i] == 'X')
        {
            pipes[i] = commandify(pipers[i], foregroundFlag, false);
        }
        else
        {
            pipes[i] = commandify(temp1, foregroundFlag, false);
            mystrcpy(redirectHere[i], trim(temp2));
        }
        // printCommand(pipes[i], 0);
        // printf("%c\n", redirectInfo[i]);
        // if (redirectInfo[i] != 'X')
        // {
        //     printf("%s\n", redirectHere[i]);
        // }
    }
    int in = 0, fileDesc[2];
    pid_t procId;
    int tempInput = dup(0);
    int tempOutput = dup(1);
    for (int i = 0; i < pipeCount - 1; i++)
    {
        pipe(fileDesc);
        handlePipedExecution(in, fileDesc[1], pipes[i]);
        close(fileDesc[1]);
        in = fileDesc[0];
    }
    if (in != 0)
    {
        dup2(in, 0);
    }
    dup2(tempOutput, 1);
    executeSingleCommand(pipes[pipeCount - 1]);
    dup2(tempInput, 0);
}