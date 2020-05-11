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

bool isLegalName(const char *name)
{
    if (name == NULL)
    {
        return false;
    }
    // Allocate new space.
    while (*name != TERMINATE)
    {
        if ((*name < FIRST_LOWER || *name > LAST_LOWER) && *name != SPACE)
        {
            return false;
        }
        name = name + 1;
    }
    return true;
}

bool isLegalId(int id)
{
    return id >= 0;
}

#endif