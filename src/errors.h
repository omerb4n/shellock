typedef enum ShellockError {
    ERROR_OK = 0,
    ERROR_MEMORY,
    ERROR_COUNT
} ShellockError;

static const char* const SHELLOCK_ERRORS_MESSAGES[] = 
{
    "OK",
    "Memory allocation error"
};
#define UNKNOWN_ERROR_MESSAGE "Unknown error"

static const char* shellock_error_str(ShellockError err);

void shellock_error(ShellockError err);