#ifndef HEADERS_H_
#define HEADERS_H_

#define _GNU_SOURCE

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
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "commands.h"
#include "prompt.h"
#include "myString.h"
#include "warp.h"
#include "peek.h"
#include "syscomm.h"
#include "pastevents.h"
#include "proclore.h"

extern char *home;
extern commandList history[15];
extern int historyCount;
extern commandList pasteveexec;
extern bool OLDPWDWARP;

#define MAX_COMMANDS 128
#define DEBUG printf("1");
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"
#endif