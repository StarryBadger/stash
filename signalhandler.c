#include "headers.h"
void handleCtrlC()
{
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