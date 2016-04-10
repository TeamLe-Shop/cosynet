#include "util.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

void error(char* msg)
{
    printf("%s: %s\n", msg, strerror(errno));
}
