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