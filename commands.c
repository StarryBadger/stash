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
// void executeSingleCommand(command cmd)
// {
//     if (equal(cmd.argv[0], "proclore"))
//         {
//             proclore(cmd);
//         }
//         else if (equal(cmd.argv[0], "warp"))
//         {
//             warp(cmd);
//         }
//         else if (equal(cmd.argv[0], "pastevents"))
//         {
//             toSave = false;
//             pastevents(cmd);
//             if (equal(cmd.argv[1], "execute"))
//             {
//                 if (toSave)
//                 {
//                     if (!toReplace)
//                     {
//                         toReplace = true;
//                         modified.count = i - 1;
//                         for (int j = 0; j < i; j++)
//                         {
//                             modified.arr[j] = toExecute.arr[j];
//                         }
//                     }
//                     for (int j = 0; j < pasteveexec.count; j++)
//                     {
//                         modified.count += 1;
//                         modified.arr[i + j] = pasteveexec.arr[j];
//                     }
//                 }
//             }

//             else
//                 toSave = false;
//         }
//         else
//             sysexec(toExecute.arr[i]);
//         modified.arr[modified.count] = toExecute.arr[i];
//         modified.count += 1;
// }
void execute(char *input)
{
    int tokenCount = 0;
    commandList toExecute;
    commandList modified;
    toExecute.count = 0;
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
    bool toSave = true, toReplace = false;
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
        else if (equal(toExecute.arr[i].argv[0], "pastevents"))
        {
            toSave = false;
            pastevents(toExecute.arr[i]);
            if (equal(toExecute.arr[i].argv[1], "execute"))
            {
                if (toSave)
                {
                    if (!toReplace)
                    {
                        toReplace = true;
                        modified.count = i - 1;
                        for (int j = 0; j < i; j++)
                        {
                            modified.arr[j] = toExecute.arr[j];
                        }
                    }
                    for (int j = 0; j < pasteveexec.count; j++)
                    {
                        modified.count += 1;
                        modified.arr[i + j] = pasteveexec.arr[j];
                    }
                }
            }

            else
                toSave = false;
        }
        else
            sysexec(toExecute.arr[i]);
        modified.arr[modified.count] = toExecute.arr[i];
        modified.count += 1;
        // free(toExecute.arr[i]); to be freed later
    }
    if (toSave)
    {
        if (!toReplace)
            saveToHistory(toExecute);
        else
            saveToHistory(modified);
    }
}