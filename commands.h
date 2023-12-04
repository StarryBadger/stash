#ifndef __COMMANDS_H
#define __COMMANDS_H
typedef struct command
{
    int argc;
    char argv[128][128];
    bool foreground;
    bool redirection; 

} command;
typedef struct commandList
{
    command arr[32];
    int count;

} commandList;
command commandify(char *str, bool stat, bool redirect);
void execute(char *);

void executeCommand(commandList);
void executeSingleCommand(command cmd);
#endif