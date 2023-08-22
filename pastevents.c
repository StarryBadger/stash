#include "headers.h"
commandList history[15];
int historyCount = 0;
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
    for (int i = 14; i >= 1; i--)
        history[i] = history[i - 1];
    history[0] = new;
    if (historyCount <= 14)
        ++historyCount;
    savePastEventsToFile(history, historyCount);
}
void pastevents()
{
    printf("%s\n", history[0].arr->argv[0]);
}
