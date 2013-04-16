#ifndef __STRARRAY_H__
#define __STRARRAY_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **strarray(char *, ...);
char **strarray_alloc(size_t);
char **strarray_realloc(char **, size_t);
void strarray_free(char **);
size_t strarray_len(char **);
char **strarray_dup(char **);
char **strarray_concat(char **, char**);
char **strarray_push(char **, char *);
char **strarray_unshift(char **, char *);
char *strarray_join(char **, char *);
char **strarray_split(char *, char *);

#define strarray_each(array, string) \
    for (int keep = 1, \
             count = 0, \
             size = strarray_len(array); \
         keep && count != size; \
         keep = !keep, count++) \
      for (string = *(array + count); keep; keep = !keep)

#endif
