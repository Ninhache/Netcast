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

#include "main.h"
#include "server.h"
#include "signals.h"
#include "utils.h"

char* message_bienvenue;
size_t welcome_length = 0;

int main(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    initialiser_signaux();
    message_bienvenue = read_file("./webserver/resources/messageBienvenue.netcast", &welcome_length);

    demarrer_serveur(DEFAULT_PORT);
    
    free(message_bienvenue);
    return EXIT_SUCCESS;
}