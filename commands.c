#include "headers.h"
command commandify(char *str, bool stat, bool redirect)
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
    cmd.foreground = stat;
    cmd.redirection = redirect;
    return cmd;
}
void execute(char *input)
{
    int tokenCount = 0;
    commandList toExecute;
    toExecute.count = 0;
    char *toExecuteStr[MAX_COMMANDS];
    bool foreground[MAX_COMMANDS];
    bool redirection[MAX_COMMANDS];
    char inputCopy[4096];
    mystrcpy(inputCopy, input);
    char *token = strtok(inputCopy, "&;");
    while (token != NULL)
    {
        char *curr = malloc(sizeof(char) * length(token) + 1);
        mystrcpy(curr, token);
        toExecuteStr[tokenCount++] = curr;
        token = strtok(NULL, "&;");
    }
    for (int i = 0; i < tokenCount; i++)
    {
        input += length(toExecuteStr[i]);
        if (input[i] == '&')
            foreground[i] = 0;
        else
            foreground[i] = 1;
    }
    for (int i = 0; i < tokenCount; i++)
    {
        command cmd = commandify(toExecuteStr[i], foreground[i], toRedirectOrPipe(toExecuteStr[i]));
        if (cmd.argc) // ensures empty commands are not added
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
    for (int i = 0; i < toExecute.count; ++i)
    {
        if (equal(toExecute.arr[i].argv[0], "pastevents"))
        {
            if (toExecute.arr[i].argc >= 2 && equal(toExecute.arr[i].argv[1], "execute"))
            {
                if (toExecute.arr[i].redirection)
                {
                    modified.arr[modified.count++] = toExecute.arr[i];
                }
                else
                {
                    if (toExecute.arr[i].argc == 2)
                    {
                        // error message: no number
                    }
                    else if (toExecute.arr[i].argc > 3)
                    {
                        // error message: too many arguments
                    }
                    else
                    {
                        int n = myatoi(toExecute.arr[i].argv[2]) - 1;
                        if (n == -1 || n >= historyCount)
                        {
                            fprintf(stderr, "\x1b[31mpastevents: %s is not a valid argument for pastevents execute\n\x1b[0m", toExecute.arr[i].argv[2]);
                            return;
                        }
                        commandList fromHistory = history[n];
                        for (int j = 0; j < fromHistory.count; j++)
                        {
                            modified.arr[modified.count++] = fromHistory.arr[j];
                        }
                    }
                }
            }
            else
            {
                modified.arr[modified.count++] = toExecute.arr[i];
                toSave = false;
            }
        }
        else
        {
            modified.arr[modified.count++] = toExecute.arr[i];
        }
    }
    for (int i = 0; i < modified.count; i++)
    {
        if (modified.arr[i].redirection)
        {
            command check = redirection(modified.arr[i]);
            if (!equal(check.argv[0], "error"))
            {
                modified.arr[i] = check;
            }
        }
        else if (equal(modified.arr[i].argv[0], "proclore"))
        {
            proclore(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "warp"))
        {
            warp(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "iMan"))
        {
            iMan(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "activities"))
        {
            activities(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "bg"))
        {
            bg(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "fg"))
        {
            fg(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "neonate"))
        {
            neonate(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "peek"))
        {
            peek(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "ping"))
        {
            ping(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "seek"))
        {
            seek(modified.arr[i]);
        }
        else if (equal(modified.arr[i].argv[0], "pastevents"))
        {
            pastevents(modified.arr[i]);
        }
        else
        {
            sysexec(modified.arr[i]);
        }
    }
    if (toSave)
    {
        saveToHistory(modified);
    }
}
void executeSingleCommand(command cmd)
{
    if (equal(cmd.argv[0], "proclore"))
    {
        proclore(cmd);
    }
    else if (equal(cmd.argv[0], "warp"))
    {
        warp(cmd);
    }
    else if (equal(cmd.argv[0], "iMan"))
    {
        iMan(cmd);
    }
    else if (equal(cmd.argv[0], "activities"))
    {
        activities(cmd);
    }
    else if (equal(cmd.argv[0], "peek"))
    {
        peek(cmd);
    }
    else if (equal(cmd.argv[0], "ping"))
    {
        ping(cmd);
    }
    else if (equal(cmd.argv[0], "bg"))
    {
        bg(cmd);
    }
    else if (equal(cmd.argv[0], "fg"))
    {
        fg(cmd);
    }
    else if (equal(cmd.argv[0], "neonate"))
    {
        neonate(cmd);
    }
    else if (equal(cmd.argv[0], "seek"))
    {
        seek(cmd);
    }
    else if (equal(cmd.argv[0], "pastevents"))
    {
        pastevents(cmd);
    }
    else
    {
        sysexec(cmd);
    }
}