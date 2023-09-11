#include"headers.h"
void bg(command cmd)
{
    if (cmd.argc ==1)
    {
        fprintf(stderr, "\x1b[31mbg: pid missing\n\x1b[0m");
        return;
    }
    if (cmd.argc >2)
    {
        fprintf(stderr, "\x1b[31mbg: bg accepts only pid as argument\n\x1b[0m");
        return;
    }
    pid_t pid;
    pid = myatoi(cmd.argv[1]);
    if (pid == -1)
    {
        fprintf(stderr, "\x1b[31mbg: pid should be a positive integer\n\x1b[0m");
        return;
    }
    kill(pid,SIGCONT);
}