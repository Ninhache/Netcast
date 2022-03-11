#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "client.h"
#include "server.h"
#include "socket.h"

void demarrer_serveur(int port) {
    int socket_serveur = creer_serveur(port);

    while (1) {
        int socket_client = creer_client(socket_serveur);

        if (socket_client == -1) {
            perror("creer_client");
            continue;
        }

        creer_processus_client(socket_client);
    }
}

void creer_processus_client (int client_socket) {
    if (fork() == 0) {
        traitement_client(client_socket);
        close(client_socket);
        exit(EXIT_SUCCESS);
    }
    // Fermeture du socket client pour le père
    close(client_socket);
}