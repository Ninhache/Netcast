#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "utils.h"
#include "socket.h"
#include "main.h"

#define UNUSED(x) (void)(x)

char* message_bienvenue;
size_t welcome_length = 0;

int main(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    int socket_serveur = creer_serveur(8080);
    initialiser_signaux();

    // run_serveur (socket_serveur (loop)

    message_bienvenue = read_file("./webserver/messageBienvenue.netcast", &welcome_length);

    while (1) {
        // creer_client (socket_serveur) -> socket_client
        int socket_client = creer_client(socket_serveur);

        if (socket_client == -1) {
            perror("creer_client");
            continue;
        }

        creer_processus_client(socket_client);
    }

    return EXIT_SUCCESS;
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

#define BUFFER_SIZE 1024
void traitement_client (int client_socket) {
        FILE* io_client = fdopen(client_socket, "a+");

        fprintf(io_client, "%s\r\n", message_bienvenue);

        /*char buffer[BUFFER_SIZE];
        while((fgets(buffer, BUFFER_SIZE, io_client)) != 0) {
            fprintf(io_client, "%s", buffer);
        }*/

        size_t line_length;
        char* line = NULL;
        while ((line = read_line(io_client, &line_length))) {
            fprintf(io_client, "<Pawnee>%s\r\n", line);

            fflush(io_client);
            free(line);
        }
        
        free(io_client);
}

void traitement_signal(int sig) {
    UNUSED(sig);
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

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