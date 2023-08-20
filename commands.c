#include "headers.h"
command *commandify(char *str)
{
    command *cmd = (command *)malloc(sizeof(command));
    cmd->argc = 0;
    char *token = strtok(str, " \n\t\r\v\f");
    printf("1\n");
    while (token != NULL)
    {
        cmd->argv[cmd->argc] = malloc(sizeof(char) * length(token + 1));
        mystrcpy(cmd->argv[cmd->argc],token);
        cmd->argc += 1;
        token = strtok(NULL, " \n\t\r\v\f");
    }
    printf("1\n");
    return cmd;
}
void execute(char *input)
{
    int tokenCount = 0, commandCount = 0;
    command *toExecute[MAX_COMMANDS];
    char *toExecuteStr[MAX_COMMANDS];
    char inputCopy[4096];
    mystrcpy(inputCopy, input);
    char *token = strtok(inputCopy, "$;\n");
    while (token != NULL)
    {
        printf(" % s\n", token);
        char *curr = malloc(sizeof(char) * length(token + 1));
        mystrcpy(curr, token);
        toExecuteStr[tokenCount++] = curr;
        token = strtok(NULL, "$;\n");   
    }
    tokenCount += 1;
    for (int i = 0; i < tokenCount; i++)
    {
        // printf("1\n");
        command *cmd = commandify(toExecuteStr[i]);
        // printf("2\n");
        if (cmd->argc)
        {
            toExecute[commandCount++] = cmd;
        }
        else
        {
            // free cmd
        }
    }
    commandCount += 1;
    for (int i = 0; i < commandCount; i++)
    {
        // if (equal(toExecute[i]->argv[0], "warp"))
        execvp(toExecute[i]->argv[0], toExecute[i]->argv);
    }
}