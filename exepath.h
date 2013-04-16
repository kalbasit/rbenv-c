#ifndef __EXEPATH_H__
#define __EXEPATH_H__

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define exepath(argv0) (__exepath ? __exepath : (__exepath = _exepath(argv0)))
char *_exepath(char *);
extern char *__exepath;

#endif
