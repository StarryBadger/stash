#include "headers.h"
int length(char *a)
{
    int c = 0;
    while (a[c] != '\0')
        ++c;
    return c;
}
bool prefix(char *a, char *b)
{
    bool flag = true;
    for (int i = 0; i < length(a); i++)
    {
        if (a[i] != b[i])
        {
            flag = false;
            break;
        }
    }
    return flag;
}
char *replaceWithTilde(char *home, char *path)
{
    char *newPath = malloc(sizeof(char) * (100));
    int c = 0;
    newPath[0] = '~';
    for (int i = length(home); i <= length(path); i++)
    {
        newPath[++c] = path[i];
    }
    return newPath;
}
char *mystrcpy(char *a, char *b)
{
    for (int i = 0; i <= length(b); i++)
    {
        a[i] = b[i];
    }
}