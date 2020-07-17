#include <stddef.h>
#include "signalock.h"

void set_sigaction(int signum, __sighandler_t handler) {
    struct sigaction s;
    s.sa_handler = handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = SA_RESTART;
    sigaction(signum, &s, NULL);
}