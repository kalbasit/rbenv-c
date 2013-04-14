#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>
#include <stdlib.h>

void begin();
void end();
void assert(int, char *);

#define streq(a, b) (a && b && strcmp(a, b) == 0)

int assertions;
int failures;

#endif
