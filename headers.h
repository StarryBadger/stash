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

extern char *home;

#include "prompt.h"
#include "myString.h"
#include "commands.h"
#include "warp.h"
#include "syscomm.h"

#define MAX_COMMANDS 128

#endif