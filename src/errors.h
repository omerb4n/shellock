typedef enum ShellockError {
    ERROR_OK = 0,
    UNKNOWN_ERROR,
    ERROR_MEMORY,
    ERROR_VALUE,
    ERROR_FORK,
    ERROR_CHILD,
    ERROR_BUILT_IN_COMMAND,
    ERROR_COUNT
} ShellockError;

void shellock_error(ShellockError err);