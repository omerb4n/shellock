#include <stddef.h>
#include "signalock.h"
#include "errors.h"

void set_sigaction(int signum, __sighandler_t handler) {
    struct sigaction s;
    s.sa_handler = handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    if (sigaction(signum, &s, NULL) != 0) {
        shellock_error(UNKNOWN_ERROR);
    }
}