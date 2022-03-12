#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

#include "client.h"
#include "server.h"
#include "socket.h"
#include "logger.h"

void demarrer_serveur(int port) {
    int socket_serveur = creer_serveur(port);

    char portNumber[4];
    sprintf(portNumber, "%d", port);
    s_log(level3, "Opening server on port :", portNumber);

    while (1) {
        s_log(level1, "Listening for connections", "...");
        int socket_client = creer_client(socket_serveur);

        if (socket_client == -1) {
            char* errStr = strerror(errno);
            s_log(level4, "Creer client", errStr);
            continue;
        }

        creer_processus_client(socket_client);
    }
}

void creer_processus_client (int client_socket) {
    s_log(level2, "Creating client", "");
    if (fork() == 0) {
        c_log(level1, "Client processing", "Starting");
        traitement_client(client_socket);
        c_log(level1, "Client processing", "Leaving");
        close(client_socket);
        c_log(level3, "Client processing", "End");
        exit(EXIT_SUCCESS);
    }
    // Fermeture du socket client pour le père
    s_log(level3, "Client socket", "End");
    close(client_socket);
}