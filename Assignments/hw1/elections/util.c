#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

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

int calculateIntegerLength(int id)
{
    if (id == 0)
        return 1;
    int count = 0;
    while (id != 0)
    {
        count++;
        id = id / 10;
    }
    return count;
}