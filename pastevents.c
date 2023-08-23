#include "headers.h"
commandList history[15];
int historyCount = 0;
commandList pasteveexec;
void savePastEventsToFile(commandList *cmdarr, int commandCount)
{
    FILE *file = fopen("history", "wb");
    if (file == NULL)
    {
        // perror("Failed to open file for writing");
        // error handling
        // return;
    }
    fwrite(&commandCount, sizeof(int), 1, file);
    for (int i = 0; i < commandCount; i++)
    {
        commandList *cmdList = &cmdarr[i];
        fwrite(cmdList, sizeof(commandList), 1, file);
    }
    fclose(file);
}
void readPastEventsFromFile(commandList *cmdarr, int *commandCount)
{
    FILE *file = fopen("history", "rb");
    if (file == NULL)
    {
        // error handling
        // perror("Failed to open file for reading");
        // return;
    }
    fread(commandCount, sizeof(int), 1, file);
    for (int i = 0; i < *commandCount; i++)
    {
        commandList *cmdList = &cmdarr[i];
        fread(cmdList, sizeof(commandList), 1, file);
    }
    fclose(file);
}
void updatePastEvents()
{
    // FILE *file = fopen("history", "r");
    // int character = fgetc(file);
    // fclose(file);
    // if (character != EOF)
    //     return;
    for (int i = 0; i < 15; i++)
    {
        history[i].count = 0;
    }
    int count = 0;
    readPastEventsFromFile(history, &count);
    historyCount = count;
}
void saveToHistory(commandList new)
{
    for (int i = historyCount - 1; i >= 1; i--)
        history[i] = history[i - 1];
    history[0] = new;
    if (historyCount <= 14)
        ++historyCount;
    savePastEventsToFile(history, historyCount);
    // printf("%d", historyCount);
}
void printCommand(command cmd, int last)
{
    for (int i = 0; i < cmd.argc; i++)
    {
        printf("%s ", cmd.argv[i]);
    }
    if (cmd.foreground && !last)
        printf("; ");
    else if (!cmd.foreground)
        printf("& ");
}
void printCommandList(commandList cmdL)
{
    for (int i = 0; i < cmdL.count; i++)
    {
        printCommand(cmdL.arr[i], (i == cmdL.count - 1)); // second parameter true only for last element
        printf("\n");
    }
}
void pastevents(command cmd)
{
    if (cmd.argc == 1)
    {
        for (int i = historyCount - 1; i >= 0; i--)
        {
            printCommandList(history[i]);
        }
    }
    if (cmd.argc == 2 && (equal(cmd.argv[1], "purge")))
    {
        {
            FILE *file = fopen("history", "w");
            historyCount = 0;
            if (file == NULL)
            {
                // perror("Failed to open file for writing");
                // error handling
            }
            fwrite(&historyCount, sizeof(int), 1, file);
            fclose(file);
        }
    }
    if (cmd.argc == 3 && equal(cmd.argv[1], "execute"))
    {
        pasteveexec = history[atoi(cmd.argv[2]) - 1];
        printCommandList(pasteveexec); // error handle for not a number and invalid numbers
    }
}