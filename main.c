#include "headers.h"
int main()
{
    char *home = homePath();
    char *prevPath = malloc(sizeof(char) * PATH_MAX);
    mystrcpy(prevPath, "\0");
    
    while (1)
    {
        prompt(home);
        char input[4096];
        fgets(input, 4096, stdin);        
        execute(input);
    }
}
