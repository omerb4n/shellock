#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static const char* SHELLOCK_ERRORS_MESSAGES[] = 
{
    "Unknown error",
    "Memory allocation error",
    "Value error",
    "Fork error",
    "Child Process error",
    "Built in command errors"
};

static const char* const shellock_error_str(ShellockError err) {
    const char* err_str = SHELLOCK_ERRORS_MESSAGES[UNKNOWN_ERROR];

    // Ensure error codes are within the valid array index range
    if (err < sizeof(SHELLOCK_ERRORS_MESSAGES))
    {
        err_str = SHELLOCK_ERRORS_MESSAGES[err];
    }
    return err_str;
}

void shellock_error(ShellockError err) {
    fprintf(stderr, "%d: %s", err, shellock_error_str(err));
    if (errno) { 
        fprintf(stderr, " (%d: %s)", errno, strerror(errno));
    }
    fprintf(stderr, "\n");
    exit(errno ? errno: -1);
}