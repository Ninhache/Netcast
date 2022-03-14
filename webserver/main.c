#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>

#include "main.h"
#include "server.h"
#include "signals.h"
#include "utils.h"
#include "logger.h"
#include "mimetype.h"

size_t welcome_length;
char* message_bienvenue;
char* document_root;

int main(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);
    
    setupLogger();

    char buf[PATH_MAX];
    document_root = realpath(argv[1], buf);
    if(document_root != NULL) {
        s_log(level2, "Setup Document root", document_root);
    } else {
        char* errStr = strerror(errno);
        s_log(level4, "Setup Document root", errStr);
        exit(EXIT_FAILURE);
    }

    message_bienvenue = read_file_path("./webserver/resources/messageBienvenue.netcast", &welcome_length);
    initialiser_signaux();

    s_log(level3, "Starting server", "");
    demarrer_serveur(DEFAULT_PORT);
    
    free(document_root);
    free(message_bienvenue);
    return EXIT_SUCCESS;
}