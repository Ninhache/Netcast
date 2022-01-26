#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "socket.h"

#define LISTEN_BACKLOG 10

int creer_serveur(int port) {
    int socket_serveur = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_serveur == -1) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET; // Socket ipv4
    saddr.sin_port = htons(port); // Port d'écoute
    saddr.sin_addr.s_addr = INADDR_ANY; // Ecouter sur toutes les interfaces

    if(bind(socket_serveur, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
        perror("bind server_socket");
        // fermer socket_serveur ici ?
        return -1;
    }

    if (listen(socket_serveur, LISTEN_BACKLOG) == -1) {
        perror("listen server_socket");
        // fermer un truc ici ?
        return -1;
    }

    return socket_serveur;
}