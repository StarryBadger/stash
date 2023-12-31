#include "headers.h"
bool pipeErrorFlag=false;
bool invalidPipe(char *piped)
{
    int len = length(piped);
    char str[len + 1];
    mystrcpy(str, piped);
    int i, j;
    for (i = 0, j = 0; i < len; i++)
    {
        if (str[i] != ' ')
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
    int length = strlen(str);
    if (str[0] == '|')
    {
        return true;
    }
    if (str[length - 1] == '|')
    {
        return true;
    }
    for (int i = 0; i < length - 1; i++)
    {
        if (str[i] == '|' && str[i + 1] == '|')
        {
            return true;
        }
    }
    return false;
}
bool toRedirectOrPipe(char *str)
{
    for (int i = 0; i < length(str); i++)
    {
        if (str[i] == '|' || str[i] == '<' || str[i] == '>')
            return true;
    }
    return false;
}
char toRedirect(char *str, char *strCmd, char *strInput, char *strOutput)
{
    int i;
    int len = strlen(str);
    int cmdEnd = -1;
    int inputStart = -1;
    int outputStart = -1;
    bool append = false;

    for (i = 0; i < len; i++)
    {
        if (str[i] == '<' || str[i] == '>')
        {
            if (cmdEnd == -1)
            {
                strncpy(strCmd, str, i);
                strCmd[i] = '\0';
                cmdEnd = i;
            }

            if (str[i] == '<')
            {
                inputStart = i + 1;
            }
            else if (str[i] == '>')
            {
                if (i + 1 < len && str[i + 1] == '>')
                {
                    outputStart = i + 2;
                    append = true;
                }
                else
                {
                    outputStart = i + 1;
                }
            }
        }
    }

    if (cmdEnd == -1)
    {
        strncpy(strCmd, str, len);
        strCmd[len] = '\0';
        return 'X';
    }

    if (inputStart != -1)
    {
        strncpy(strInput, str + inputStart, len - inputStart);
        strInput[len - inputStart] = '\0';
    }

    if (outputStart != -1)
    {
        strncpy(strOutput, str + outputStart, len - outputStart);
        strOutput[len - outputStart] = '\0';
    }

    if (inputStart != -1 && outputStart != -1)
    {
        if (append)
        {
            return 'A';
        }
        else
        {
            return 'W';
        }
    }
    else if (inputStart != -1)
    {
        return 'R';
    }
    else if (outputStart != -1)
    {
        if (append)
        {
            return 'A';
        }
        else
        {
            return 'W';
        }
    }

    return 'X';
}
void convertPipesToString(int pipeCount, command pipes[pipeCount], char redirectInfo[pipeCount], char redirectFrom[pipeCount][64], char redirectTo[pipeCount][64], char cmdStr[PATH_MAX])
{
    cmdStr[0] = '\0';
    for (int i = 0; i < pipeCount; ++i)
    {
        for (int j = 0; j < pipes[i].argc; j++)
        {
            strcat(cmdStr, pipes[i].argv[j]);
            strcat(cmdStr, " ");
        }
        if (length(redirectFrom[i]))
        {
            strcat(cmdStr, "< ");
            strcat(cmdStr, redirectFrom[i]);
            strcat(cmdStr, " ");
        }
        if (length(redirectTo[i]))
        {
            if (redirectInfo[i] == 'A')
            {
                strcat(cmdStr, ">> ");
                strcat(cmdStr, redirectTo[i]);
            }
            else
            {
                strcat(cmdStr, "> ");
                strcat(cmdStr, redirectTo[i]);
            }
        }
        if (i != pipeCount - 1)
            strcat(cmdStr, "| ");
    }
}
command redirection(command cmd)
{
    char pipers[16][128];
    char comm[128], input[128], output[128];
    char cmdStr[PATH_MAX];
    char cmdStrCopy[PATH_MAX];
    cmdStr[0] = '\0';
    for (int i = 0; i < cmd.argc; i++)
    {
        strcat(cmdStr, cmd.argv[i]);
        strcat(cmdStr, " ");
    }
    if (invalidPipe(cmdStr))
    {
        fprintf(stderr, "\x1b[31mInvalid use of pipe\n\x1b[0m");
        command cmdErr = commandify("error", cmd.foreground, true);
        return cmdErr;
    }
    char *token = strtok(cmdStr, "|");
    int pipeCount = 0;
    while (token != NULL)
    {
        mystrcpy(pipers[pipeCount], token);
        pipeCount += 1;
        token = strtok(NULL, "|");
    }
    command pipes[16];
    char redirectInfo[16];
    char redirectFrom[16][64];
    char redirectTo[16][64];
    for (int i = 0; i < pipeCount; ++i)
    {
        input[0] = '\0';
        output[0] = '\0';
        bool foregroundFlag = true;
        if (i == pipeCount - 1)
        {
            foregroundFlag = cmd.foreground;
        }
        redirectInfo[i] = toRedirect(pipers[i], comm, input, output);
        pipes[i] = commandify(comm, foregroundFlag, false);
        pipes[i] = pasteventsExecuteCheck(pipes[i]);
        removeOddArrows(input);
        removeOddArrows(output);
        mystrcpy(redirectFrom[i], trim(input));
        mystrcpy(redirectTo[i], trim(output));

        // printCommand(pipes[i], 0);
        // printf("%c\n", redirectInfo[i]);
        // printf("Redirected from: %s\n", redirectFrom[i]);
        // printf("Redirected to: %s\n", redirectTo[i]);
    }
    convertPipesToString(pipeCount, pipes, redirectInfo, redirectFrom, redirectTo, cmdStr);
    if (invalidPipe(cmdStr))
    {
        fprintf(stderr, "\x1b[31mInvalid use of pipe\n\x1b[0m");
        command cmdErr = commandify("error", cmd.foreground, true);
        return cmdErr;
    }
    pipeCount = 0;
    mystrcpy(cmdStrCopy, cmdStr);
    token = strtok(cmdStr, "|");
    while (token != NULL)
    {
        mystrcpy(pipers[pipeCount], token);
        pipeCount += 1;
        token = strtok(NULL, "|");
    }
    for (int i = 0; i < pipeCount; ++i)
    {
        input[0] = '\0';
        output[0] = '\0';
        bool foregroundFlag = true;
        if (i == pipeCount - 1)
        {
            foregroundFlag = cmd.foreground;
        }
        redirectInfo[i] = toRedirect(pipers[i], comm, input, output);
        pipes[i] = commandify(comm, foregroundFlag, false);
        removeOddArrows(input);
        removeOddArrows(output);
        mystrcpy(redirectFrom[i], trim(input));
        mystrcpy(redirectTo[i], trim(output));
    }
    int in = 0, fileDesc[2], outfile;
    int tempInput = dup(0);
    int tempOutput = dup(1);
    for (int i = 0; i < pipeCount; i++)
    {
        pipe(fileDesc);
        if (length(redirectFrom[i]))
        {
            in = open(redirectFrom[i], O_RDONLY);
            if (in == -1)
            {
                fprintf(stderr, "\x1b[31mNo such input file found!\n\x1b[0m");
                command cmdErr = commandify("error", cmd.foreground, true);
                return cmdErr;
            }
        }
        if (length(redirectTo[i]))
        {
            if (redirectInfo[i] == 'W')
            {
                outfile = open(redirectTo[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
            }
            else
            {
                outfile = open(redirectTo[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
            }
            dup2(outfile, 1);
        }
        if (in != 0)
        {
            dup2(in, 0);
        }
        if (i == pipeCount - 1 && !length(redirectTo[i]))
        {
            dup2(tempOutput, 1);
        }
        else if (fileDesc[1] != 1 && !length(redirectTo[i]))
        {
            dup2(fileDesc[1], 1);
        }
        executeSingleCommand(pipes[i]);
        close(fileDesc[1]);
        if (i != 0)
        {
            close(in);
        }
        if (length(redirectTo[i]))
        {
            dup2(tempOutput, 1);
            in = fileDesc[0];
        }
        else
        {
            in = fileDesc[0];
        }
    }
    dup2(tempInput, 0);
    dup2(tempOutput, 1);
    command cmdRet = commandify(cmdStrCopy, cmd.foreground, true);
    return cmdRet;
}
