#ifndef __COMMANDS_H
#define __COMMANDS_H
typedef struct command
{
    int argc;
    char *argv[256];
    bool foreground; 

} command;
command *commandify(char *str, bool stat);
void execute(char*);
void freeCommand(command *);
#endif