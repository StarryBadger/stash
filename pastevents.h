#ifndef __PASTEVENTS_H
#define __PASTEVENTS_H
void savePastEventsToFile(commandList *cmdarr, int commandCount);
void readPastEventsFromFile(commandList *cmdarr, int *commandCount);
void saveToHistory(commandList);
void pastevents(command cmd);
void printCommandList(commandList cmdL);
void printCommand(command cmd, int last);
command pasteventsExecuteCheck(command cmd);
#endif