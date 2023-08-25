#include "headers.h"
char *home;
char timetaker[PATH_MAX];
int timetakertime;
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
    mystrcpy(timetaker, "\0");
    timetakertime = 0;
    home = homePath();
    readPastEventsFromFile(history, &historyCount);
    while (1)
    {
        prompt();
        char input[4096];
        fgets(input, 4096, stdin);
        time_t beforeCode;
        time(&beforeCode);
        execute(input);
        time_t afterCode;
        time(&afterCode);
        char *token = strtok(input, " \n\t\r\v\f");
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
