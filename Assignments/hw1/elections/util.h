#ifndef UTIL_H
#define UTIL_H

#define FIRST_LOWER 'a'
#define LAST_LOWER 'z'
#define SPACE ' '
#define TERMINATE '\0'

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isLegalName(const char *name);
bool isLegalId(int id);
int calculateIntegerLength(int id);
#endif