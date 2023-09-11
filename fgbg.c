#include "headers.h"
int foregroundMaker(int pid)
{
    setpgid(pid, 0);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, pid);

    int status;
    waitpid(pid,&status,WUNTRACED);

    tcsetpgrp(STDIN_FILENO, getpgid(0));    
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    return status;
}
void bg(command cmd)
{
    if (cmd.argc == 1)
    {
        fprintf(stderr, "\x1b[31mbg: pid missing\n\x1b[0m");
        return;
    }
    if (cmd.argc > 2)
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
    kill(pid, SIGCONT);
}
void fg(command cmd)
{
    if (cmd.argc == 1)
    {
        fprintf(stderr, "\x1b[31mfg: pid missing\n\x1b[0m");
        return;
    }
    if (cmd.argc > 2)
    {
        fprintf(stderr, "\x1b[31mfg: fg accepts only pid as argument\n\x1b[0m");
        return;
    }
    pid_t pid;
    pid = myatoi(cmd.argv[1]);
    if (pid == -1)
    {
        fprintf(stderr, "\x1b[31mfg: pid should be a positive integer\n\x1b[0m");
        return;
    }
    kill(pid, SIGCONT);
    int status=foregroundMaker(pid);
    // removeNode(bglist,pid);
}
