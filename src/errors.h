typedef enum ShellockError {
    ERROR_OK = 0,
    ERROR_MEMORY,
    ERROR_VALUE,
    ERROR_FORK,
    ERROR_CHILD,
    ERROR_BUILT_IN_COMMAND,
    ERROR_COUNT
} ShellockError;

#define UNKNOWN_ERROR_MESSAGE "Unknown error"

void shellock_error(ShellockError err);