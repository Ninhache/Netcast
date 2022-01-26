#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "socket.h"

#define UNUSED(x) (void)(x)

int main(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    int socket_serveur = creer_serveur(8080);

    while (1) {
        int socket_client = accept(socket_serveur, NULL, NULL);
        if (socket_client == -1) {
            perror("accept client_socket");
            continue;
        }

        const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur\n";
        write(socket_client, message_bienvenue, strlen(message_bienvenue));

        // fflush(socket_client) ???
        // close(socket_client) ??? [+ perror]
    }

    return EXIT_SUCCESS;
}