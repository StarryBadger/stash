#include "headers.h"
command *commandify(char *str, bool stat)
{
    command *cmd = (command *)malloc(sizeof(command));
    cmd->argc = 0;
    char *token = strtok(str, " \n\t\r\v\f");
    while (token != NULL)
    {
        cmd->argv[cmd->argc] = malloc(sizeof(char) * length(token + 1));
        mystrcpy(cmd->argv[cmd->argc], token);
        cmd->argc += 1;
        token = strtok(NULL, " \n\t\r\v\f");
    }
    cmd->argv[cmd->argc] = NULL;
    cmd->foreground = stat;
    return cmd;
}
void freeCommand(command *cmd)
{
    for (int i = 0; i < cmd->argc; i++)
        free(cmd->argv[i]);
    free(cmd);
}
void execute(char *input)
{
    int tokenCount = 0, commandCount = 0;
    command *toExecute[MAX_COMMANDS];
    char *toExecuteStr[MAX_COMMANDS];
    bool foreground[MAX_COMMANDS];
    char inputCopy[4096];
    mystrcpy(inputCopy, input);
    char *token = strtok(inputCopy, "$;\n");
    while (token != NULL)
    {
        char *curr = malloc(sizeof(char) * length(token) + 1);
        mystrcpy(curr, token);
        toExecuteStr[tokenCount++] = curr;
        token = strtok(NULL, "$;\n");
    }
    for (int i = 0; i < tokenCount; i++)
    {
        input += length(toExecuteStr[i]);
        if (input[i] == ';' || input[i] == '\n')
            foreground[i] = 1;
        else
            foreground[i] = 0;
    }
    for (int i = 0; i < tokenCount; i++)
    {
        command *cmd = commandify(toExecuteStr[i], foreground[i]);
        if (cmd->argc)
            toExecute[commandCount++] = cmd;
        else
            freeCommand(cmd);
    }
    for (int i = 0; i < commandCount; i++)
    {
        if (equal(toExecute[i]->argv[0], "warp"))
            warp(toExecute[i]);
        else
            sysexec(toExecute[i]);
        free(toExecute[i]);
    }
}