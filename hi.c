#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <limits.h>
int length(char *a)
{
    int c = 0;
    while (a[c] != '\0')
        ++c;
    return c;
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
int main()
{
    // char *hi = malloc(sizeof(char) * 100);
    // getcwd(hi, sizeof(hi));
    // printf("Current working dir: %s\n", hi);
    char a[10]="Hello";
    char b[11]="Hellobitch";
    printf("%s",replaceWithTilde(a,b));
}