#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "commands.h"
#include "prompt.h"
#include "myString.h"
#include "warp.h"
#include "syscomm.h"
#include "pastevents.h"
#include "proclore.h"
extern char *home;
extern commandList history[15];
extern int historyCount;
extern commandList pasteveexec;
extern bool OLDPWD;
#define MAX_COMMANDS 128
#define DEBUG printf("1\n");
#endif