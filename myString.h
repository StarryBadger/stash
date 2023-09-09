#ifndef __MYSTRING_H
#define __MYSTRING_H
int length(char *);
bool prefix(char *, char *);
char *replaceHomeWithTilde(char *);
char *replaceTildeWithHome(char *);
char *mystrcpy(char *, char *);
char *removeSubstring(char *, char *);
bool equal(char *, char *);
int myatoi(char *str);
bool equalNameWithExtension(char* file, char* search);
bool myIsspace(char c);
char* trim(char *str);
void removeOddArrows(char *str);
#endif
