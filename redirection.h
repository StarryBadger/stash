#ifndef __REDIRECTION_H
#define __REDIRECTION_H
bool toRedirectOrPipe(char* str);
command redirection(command);
void convertPipesToString(int pipeCount, command pipes[pipeCount], char redirectInfo[pipeCount], char redirectFrom[pipeCount][64], char redirectTo[pipeCount][64], char cmdStr[PATH_MAX]);
#endif