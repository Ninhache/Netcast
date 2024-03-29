#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "socket.h"
#include "logger.h"

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

    int optval = 1;
    if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1) {
        perror("setsockopt SO_REUSEADDR");
    }

    if (bind(socket_serveur, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
        perror("bind server_socket");
        close(socket_serveur);
        return -1;
    }

    if (listen(socket_serveur, LISTEN_BACKLOG) == -1) {
        perror("listen server_socket");
        close(socket_serveur);
        return -1;
    }

    return socket_serveur;
}

int creer_client(int server_socket) {
//    struct sockaddr* client_addr = malloc(sizeof(struct sockaddr)); 
    int client_socket = accept(server_socket, NULL, NULL);
    // Recup le 2e param pour savoir d'où ça vient !
    s_log(level2, "Connexion from", "somewhere");

    if (client_socket == -1) {
        perror("accept client_socket");
        return -1;
    }
    
    return client_socket;
}
