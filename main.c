#include "headers.h"
PtrNode bglist;
char *home;
char timetaker[PATH_MAX];
char inp[PATH_MAX];
int userInputLength;
int timetakertime;
int pt;
bool toReprintPrompt = true;
char *homePath()
{
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    char *path = malloc(sizeof(char) * (length(cwd + 1)));
    mystrcpy(path, cwd);
    return path;
}
int main()
{
    bglist = initializeList();
    mystrcpy(timetaker, "\0");
    timetakertime = 0;
    home = homePath();
    readPastEventsFromFile(history, &historyCount);
    struct sigaction sa;
    sa.sa_handler = handleCtrlC;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGTSTP,SIG_IGN);
    while (1)
    {
        prompt();
        char input[4096];
        // fgets(input, 4096, stdin);
        char c;
        setbuf(stdout, NULL);
        enableRawMode();
        memset(inp, '\0', 100);
        pt = 0;
        while (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (iscntrl(c))
            {
                if (c == 10)
                    break;
                else if (c == 127)
                { // backspace
                    if (pt > 0)
                    {
                        if (inp[pt - 1] == 9)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        inp[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == 9)
                { // TAB character
                    inp[pt++] = c;
                    for (int i = 0; i < 8; i++)
                    {
                        printf(" ");
                    }
                }
                else if (c == 4)
                {
                    printf("\n");
                    exit(0);
                }
            }
            else
            {
                inp[pt++] = c;
                printf("%c", c);
            }
        }
        inp[pt++] = '\0';
        disableRawMode();
        printf("\n");
        mystrcpy(input, inp);
        findKilled();
        time_t beforeCode;
        time(&beforeCode);
        toReprintPrompt=false;
        execute(input);
        toReprintPrompt=true;
        time_t afterCode;
        time(&afterCode);
        char *token = strtok(inp, " \n\t\r\v\f");
        timetakertime = afterCode - beforeCode;
        if (timetakertime > 2)
        {
            mystrcpy(timetaker, token);
        }
        else
        {
            mystrcpy(timetaker, "\0");
        }
    }
    free(home);
}
