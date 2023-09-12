#include "headers.h"
void handleCtrlC()
{
    PtrNode current = bglist;
    if (toReprintPrompt)
    {
        printf("^C");
        timetakertime = 0;
        printf("\n");
        prompt();
        inp[0] = '\0';
        pt = 0;
    }
    else
    {
        printf("\n");
    }
}
void handleAlarm()
{
    if (!xReceived)
    {
        printLatestProcess();
        alarm(alarmTime);
    }
}
int kbhit()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}