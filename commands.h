#ifndef __COMMANDS_H
#define __COMMANDS_H
typedef struct command
{
    int argc;
    char *argv[256];
    // char argv[256][256];
    bool foreground;

} command;
typedef struct commandList
{
    command *arr[PATH_MAX];
    // command arr[PATH_MAX];
    int count;

} commandList;
command *commandify(char *str, bool stat);
void execute(char *);
void freeCommand(command *);
#endif