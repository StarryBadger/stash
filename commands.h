#ifndef __COMMANDS_H
#define __COMMANDS_H
typedef struct command
{
    int argc;
    // char *argv[256];
    char argv[128][128];
    bool foreground;

} command;
typedef struct commandList
{
    // command *arr[PATH_MAX];
    command arr[20];
    int count;

} commandList;
command commandify(char *str, bool stat);
void execute(char *);
void freeCommand(command *);
#endif