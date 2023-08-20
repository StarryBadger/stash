#ifndef __COMMANDS_H
#define __COMMANDS_H
typedef struct command
{
    int argc;
    char *argv[256];
    bool foreground; 

} command;
void execute(char*);
#endif