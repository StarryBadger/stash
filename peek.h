#ifndef __PEEK_H
#define __PEEK_H
void peek(command);
void peekL(char *path, const char *filename);
void peekJist(char *path, const char *filename);
void totalBlockSize(char *path, const char *filename);
void setFlags(char *flags, bool *L, bool *A);
#endif