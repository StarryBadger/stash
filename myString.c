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
char *removeSubstring(char *substr, char *str)
{
    char *newstr = malloc(sizeof(char) * (100));
    int c = 0;
    for (int i = length(substr); i <= length(str); i++)
    {
        newstr[c++] = str[i];
    }
    return newstr;
}
char *replaceHomeWithTilde(char *path)
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
char *replaceTildeWithHome(char *path)
{
    char *newPath = malloc(sizeof(char) * (PATH_MAX + 1));
    int c = 0;
    mystrcpy(newPath, home);
    for (int i = length(home); c <= length(path); i++)
    {
        newPath[i] = path[++c];
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
bool equal(char *a, char *b)
{
    int i = 0;
    while (true)
    {
        if (!a[i] & !b[i])
            return true;
        else if ((!a[i] ^ !b[i]) || (a[i] != b[i]))
            return false;
        i++;
    }
}
int myatoi(char *str)
{
    int n = 0;
    for (int i = 0; i < length(str); i++)
    {

        int num = (int)str[i] - 48;
        if (num >= 0 && num <= 9)
            n = n * 10 + num;
        else
            return -1;
    }
    return n;
}
bool equalNameWithExtension(char *file, char *search)
{
    int i;
    if (!prefix(search, file))
        return false;
    for (i = length(file) - 1; i >= 0; i--)
        if (file[i] == '.')
            break;
    if (i == -1)
        return equal(file, search);
    for (i = length(search) - 1; i >= 0; i--)
        if (search[i] == '.')
            return false;

    int j = 0;
    while (j < i)
    {
        if (file[j] != search[j])
            return false;
        j++;
    }
    return true;
}