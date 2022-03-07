#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

#include "utils.h"
#include "signals.h"

void initialiser_signaux (void) {
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
    }

    struct sigaction sa;
    sa.sa_handler = traitement_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction(SIGCHLD)");
    }
}

void traitement_signal(int sig) {
    UNUSED(sig);
    while (waitpid(-1, NULL, WNOHANG) > 0);
}