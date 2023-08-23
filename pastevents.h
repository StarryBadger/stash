#ifndef __PASTEVENTS_H
#define __PASTEVENTS_H
void savePastEventsToFile(commandList *cmdarr, int commandCount);
void readPastEventsFromFile(commandList *cmdarr, int *commandCount);
void updatePastEvents(); // updates array of past events and ists count
// void updateHistoryFile(int commandCount, commandList history[15]); //updates history file
void saveToHistory(commandList); // adds prompt to history and updates file
void pastevents(command cmd);
void printCommandList(commandList cmdL);
void printCommand(command cmd, int last);
#endif