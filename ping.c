#include "headers.h"
void ping(command cmd)
{
    if (cmd.argc != 3)
    {
        fprintf(stderr, "\x1b[31mping: ping accepts 2 arguments\n\x1b[0m");
        return;
    }
    pid_t pid;
    int signum;
    pid = myatoi(cmd.argv[1]);
    signum = myatoi(cmd.argv[2]);
    if (pid == -1)
    {
        fprintf(stderr, "\x1b[31mping: pid should be a positive integer\n\x1b[0m");
        return;
    }
    if (signum == -1)
    {
        fprintf(stderr, "\x1b[31mping: signal number should be a positive integer\n\x1b[0m");
        return;
    }
    signum = signum % 32;
    int status = kill(pid, signum);
    if (status!=0)
    fprintf(stderr, "\x1b[31mNo such process found\n\x1b[0m");
    else
    printf("Sent signal %d to process with pid %d\n",pid,signum);
}