#include "headers.h"
int alarmTime;
bool xReceived;
void printLatestProcess()
{
    FILE *file = fopen("/proc/loadavg", "r");
    char TEMP[100];
    pid_t pid;
    fscanf(file, "%s %s %s %s %d", TEMP, TEMP, TEMP, TEMP, &pid);
    fclose(file);
    printf("%d\n", pid);
}
void neonate(command cmd)
{
    xReceived = false;
    if (cmd.argc > 1 && !equal(cmd.argv[1], "-n"))
    {
        fprintf(stderr, "\x1b[31mneonate: use of -n flag is compulsory\n\x1b[0m");
        return;
    }
    else if (cmd.argc != 3)
    {
        fprintf(stderr, "\x1b[31mneonate: neonate accepts time_arg as argument\n\x1b[0m");
        return;
    }
    alarmTime = myatoi(cmd.argv[2]);
    if (alarmTime == -1)
    {
        fprintf(stderr, "\x1b[31mneonate: time_arg should be a positive integer\n\x1b[0m");
        return;
    }
    enableRawMode();
    printLatestProcess();
    alarm(alarmTime);
    int ch;
    while (1)
    {
        char ch;
        read(0, &ch, 1);
        if (ch == 'x')
        {
            xReceived = true;
            break;
        }
    }
    disableRawMode();
    return;
}