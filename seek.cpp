#include "headers.h"
int foundcount = 0;
int pathlength;
char executeMe[PATH_MAX];
bool setSeekFlags(char *input, bool *F, bool *E, bool *D, bool *returnControl)
{
    if (equal(input, "-e") ||
        equal(input, "-f") ||
        equal(input, "-ef") ||
        equal(input, "-fe") ||
        equal(input, "-ed") ||
        equal(input, "-de"))
    {
        for (int i = 0; i < length(input); i++)
        {
            if (input[i] == 'f')
            {
                *F = true;
                if (*D)
                {
                    fprintf(stderr, "\x1b[31mseek: Invalid flags\x1b[0m");
                    *returnControl = true;
                    return false;
                }
            }
            else if (input[i] == 'd')
            {
                *D = true;
                if (*F)
                {
                    fprintf(stderr, "\x1b[31mseek: Invalid flags\x1b[0m");
                    *returnControl = true;
                    return false;
                }
            }
            else if (input[i] == 'e')
            {
                *E = true;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
void lookFor(bool *D, bool *F, char *target, char *path)
{
    DIR *directory = opendir(path);
    if (directory == NULL)
        return;
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL)
    {
        if (equal(entry->d_name, ".") || equal(entry->d_name, ".."))
            continue;
        char pathBranch[PATH_MAX];
        mystrcpy(pathBranch, path);
        if (pathBranch[length(pathBranch) - 1] != '/')
            strcat(pathBranch, "/");
        strcat(pathBranch, entry->d_name);
        struct stat st;
        if (stat(pathBranch, &st) == -1)
            continue;
        if (S_ISDIR(st.st_mode))
        {
            if (equal(entry->d_name, target) && D)
            {
                printf(BLUE ".%s\n" RESET, pathBranch + pathlength);
                foundcount++;
                mystrcpy(executeMe, pathBranch);
            }
            lookFor(D, F, target, pathBranch);
        }
        else if (S_ISREG(st.st_mode) && F)
        {
            if (equal(entry->d_name, target) || equalNameWithExtension(entry->d_name, target))
            {
                printf(GREEN ".%s\n" RESET, pathBranch + pathlength);
                foundcount++;
                mystrcpy(executeMe, pathBranch);
            }
        }
    }
    closedir(directory);
}
void seek(command cmd)
{
    foundcount = 0;
    bool returnControl = false;
    bool F = false, E = false, D = false;
    char target[PATH_MAX], path[PATH_MAX];
    getcwd(path, PATH_MAX - 1);
    int i = 1;
    while (setSeekFlags(cmd.argv[i++], &F, &E, &D, &returnControl))
    {
        if (i == cmd.argc)
            break;
    }
    if (returnControl)
        return;
    if (i == cmd.argc)
    {
        fprintf(stderr, "\x1b[31mseek: No target file/directory\n\x1b[0m");
        return;
    }
    mystrcpy(target, cmd.argv[i]);
    if (i != cmd.argc - 1)
        mystrcpy(path, cmd.argv[++i]);
    else
        getcwd(path, PATH_MAX - 1);
    if (i != cmd.argc - 1)
    {
        fprintf(stderr, "\x1b[31mseek: Multiple file paths detected\n\x1b[0m");
        return;
    }
    if (!F && !D)
    {
        F = true;
        D = true;
    }
    if (prefix("~", path))
    {
        mystrcpy(path, replaceTildeWithHome(path));
    }
    pathlength = length(path);
    lookFor(&D, &F, target, path);
    if (foundcount == 0)
    {
        printf("No match found!\n");
    }
    if (E)
    {
        if (foundcount == 1)
        {
            struct stat st;
            stat(executeMe, &st);
            if (S_ISDIR(st.st_mode))
            {
                chdir(executeMe);
            }
            else if (S_ISREG(st.st_mode))
            {
                FILE *file = fopen(executeMe, "r");
                if (file == NULL)
                {
                    fprintf(stderr, "\x1b[31mseek: can't open file: Permission denied\n\x1b[0m");
                    return;
                }
                char ch;
                while ((ch = fgetc(file)) != EOF)
                    putchar(ch);
                printf("\n");
                fclose(file);
            }
        }
        else if (foundcount > 2)
        {
            fprintf(stderr, "\x1b[31mseek: can't execute more than one file/directory\n\x1b[0m");
            return;
        }
    }
}
