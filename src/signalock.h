#ifndef _SIGNALLCOK
#define _SIGNALLCOK

#include <signal.h>

void set_sigaction(int signum, __sighandler_t handler);

#endif
