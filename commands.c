#include "headers.h"
command commandify(char *str, bool stat)
{
    command cmd;
    cmd.argc = 0;
    char *token = strtok(str, " \n\t\r\v\f");
    while (token != NULL)
    {
        mystrcpy(cmd.argv[cmd.argc], token);
        cmd.argc += 1;
        token = strtok(NULL, " \n\t\r\v\f");
    }
    // cmd.argv[cmd.argc] = NULL; MAKE NULL FOR EXECVP LATER
    cmd.foreground = stat;
    return cmd;
}
void execute(char *input)
{
    int tokenCount = 0;
    commandList toExecute;
    toExecute.count = 0;
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
        command cmd = commandify(toExecuteStr[i], foreground[i]);
        if (cmd.argc)
        {
            toExecute.arr[toExecute.count++] = cmd;
        }
    }
    executeCommand(toExecute);
}
void executeCommand(commandList toExecute)
{
    commandList modified;
    modified.count = 0;
    bool toSave = true;
    bool toReplace = false;
    for (int i = 0; i < toExecute.count; i++)
    {
        if (equal(toExecute.arr[i].argv[0], "proclore"))
        {
            proclore(toExecute.arr[i]);
        }
        else if (equal(toExecute.arr[i].argv[0], "warp"))
        {
            warp(toExecute.arr[i]);
        }
        else if (equal(toExecute.arr[i].argv[0], "peek"))
        {
            peek(toExecute.arr[i]);
        }
        else if (equal(toExecute.arr[i].argv[0], "seek"))
        {
            seek(toExecute.arr[i]);
        }
        else if (equal(toExecute.arr[i].argv[0], "pastevents"))
        {
            pastevents(toExecute.arr[i]);
            if (equal(toExecute.arr[i].argv[1], "execute"))
            {
                toReplace = true;
                if (toSave)
                {
                    for (int j = 0; j < pasteveexec.count; j++)
                    {
                        modified.arr[modified.count + j] = pasteveexec.arr[j];
                        ++modified.count;
                    }
                }
            }
            else
            {
                toSave = false;
            }
        }
        else
        {
            sysexec(toExecute.arr[i]);
        }
        if (!toReplace)
        {
            modified.arr[modified.count] = toExecute.arr[i];
            modified.count += 1;
        }
        // free(toExecute.arr[i]); to be freed later
    }
    if (toSave)
    {
        if (!toReplace)
        {
            saveToHistory(toExecute);
        }
        else
        {
            saveToHistory(modified);
        }
    }
}