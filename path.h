#ifndef __PATH_H__
#define __PATH_H__

#include "strarray.h"

#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *getpwd();
char *dirname(char *);
char *abs_dirname(char *);
int cd(char *);
char *join_path(char *, char *);
char **wildcard_paths(char *, ...);
char *trim_trailing_slash(char *);
void truncate_path(char *);

#endif
