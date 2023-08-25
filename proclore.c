#include "headers.h"
void proclore(command cmd)
{
    int pid;
    if (cmd.argc > 2)
    {
        // throw error
    }
    if (cmd.argc == 2)
    {
        
        pid = myatoi(cmd.argv[1]);
        if (pid==-1)
        {
            
        }
    }
    else
    {
        pid = getpid();
    }
    char stat[25] = "\0";
    sprintf(stat, "/proc/%d/stat", pid);
    FILE *file = fopen(stat, "r");
    if (file == NULL)
    {
        perror("Failed to open stat file");
        // error handling
    }
    int pgrp;
    char state;
    char executable[256];
    unsigned long int vsize;
    char exe[25] = "\0";
    char TEMP[100];
    fscanf(file, "%d (%[^)]) %c %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %S %s %lu (%[^\n]s)", &pid, TEMP, &state, TEMP, &pgrp, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, TEMP, &vsize, TEMP);
    sprintf(exe, "/proc/%d/exe", pid);
    readlink(exe, executable, 255);
    int pargrp = getpgrp();
    // write exclusively for all parents
    if (prefix(home, executable))
    {
        mystrcpy(executable, replaceHomeWithTilde(executable));
    }
    char stateStr[3];
    stateStr[0] = state;
    stateStr[1] = '\0';
    if (pgrp == pargrp)
    {
        strcat(stateStr, "+");
    }
    printf("pid : %d\nprocess Status : %s\nProcess Group : %d\nVirtual memory : %lu\nexecutable Path : %s\n", pid, stateStr, pgrp, vsize, executable);
    fclose(file);
}