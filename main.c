#include "headers.h"
int main()
{
    char *home = homePath();
    while (1)
    {
        prompt(home);
        char input[4096];
        fgets(input, 4096, stdin);
        if (prefix("warp",input))
        warp(input);
    }
}
