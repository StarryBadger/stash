#ifndef __COMMANDS_H
#define __COMMANDS_H
typedef struct command
{
    int argc;
    char argv[128][128];
    bool foreground;

} command;
typedef struct commandList
{
    command arr[50];
    int count;

} commandList;
command commandify(char *str, bool stat);
void execute(char *);

void executeCommand(commandList);
#endif