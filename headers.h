#ifndef HEADERS_H_
#define HEADERS_H_

#define _GNU_SOURCE

#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <stdio.h>
#include <limits.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "signalhandler.h"
#include "commands.h"
#include "prompt.h"
#include "myString.h"
#include "warp.h"
#include "peek.h"
#include "syscomm.h"
#include "pastevents.h"
#include "proclore.h"
#include "seek.h"
#include "background.h"
#include "redirection.h"
#include "activities.h"
#include "ping.h"
#include "raw.h"
#include "fgbg.h"
#include "neonate.h"

extern char *home;
extern commandList history[15];
extern int historyCount;
extern commandList pasteveexec;
extern bool OLDPWDWARP;
extern off_t total_block_size;
extern int foundcount;
extern char executeMe[PATH_MAX];
extern int pathlength;
extern char timetaker[PATH_MAX];

extern int timetakertime;
extern PtrNode bglist;
extern bool toReprintPrompt;
extern char inp[PATH_MAX];
extern int pt;
extern int alarmTime;
extern bool xReceived;

#define MAX_COMMANDS 128
#define DEBUG printf("1\n");
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#endif