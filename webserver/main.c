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
int welcome_length = -1;

int main(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    int socket_serveur = creer_serveur(8080);
    initialiser_signaux();

    // run_serveur (socket_serveur (loop)

    message_bienvenue = read_file("./webserver/messageBienvenue.netcast", &welcome_length);

    while (1)
    {
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

    close(client_socket);
}

void traitement_client (int client_socket) {

        for (int i = 0; i < 10; ++i) {
            write(client_socket, message_bienvenue, welcome_length);
            sleep(1);
        }
        
}

void traitement_signal(int sig)
{
    printf("Signal %d reçu\n", sig);    
    waitpid(-1, NULL, WNOHANG);
}

void initialiser_signaux (void) {
 
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        perror("signal");
    }

    struct sigaction sa;
    sa.sa_handler = traitement_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == SIG_ERR)
    {
        perror("sigaction(SIGCHLD)");
    }

}