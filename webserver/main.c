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

#include "utils.h"
#include "socket.h"
#include "main.h"

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
    free(message_bienvenue);
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

void traitement_client (int client_socket) {
    FILE* io_client = fdopen(client_socket, "a+");


    // Traitement de la reqûete HTTP
    //size_t line_length;
    char buffer_line[HTTP_LINE_LENGTH];
    fgets_or_exit(buffer_line, HTTP_LINE_LENGTH, io_client);
    //line_length = strlen(buffer_line);

    printf("[0] %s", buffer_line);

    if(strcmp(buffer_line, "GET / HTTP/1.1\r\n") == 0) {
        printf("[1] VALID REQUEST (GET)\n");
        printf("[1] SENDING WELCOME MESSAGE\n");
        printf("[1] PROCESSING HEADER LINES\n");

        skip_header(io_client);

        printf("[1] REPLYING TO CLIENT REQUEST (200 OK)\n");
        fprintf(io_client, "HTTP/1.1 200 OK\r\n");
        fprintf(io_client, "Content-Length: %ld\r\n\r\n", welcome_length);
        fprintf(io_client, "%s\r\n", message_bienvenue);
    } else if (strcmp(buffer_line, "GET /inexistant HTTP/1.1\r\n") == 0) {
        skip_header(io_client);
        printf("[1] FILE NOT FOUND\n");
        printf("[1] REPLYING TO CLIENT REQUEST (404 Not Found)\n");
        fprintf(io_client, "HTTP/1.1 404 Not Found\r\n");
        fprintf(io_client, "Connection: close\r\n");
        fprintf(io_client, "Content-Length: 15\r\n");
        fprintf(io_client, "\r\n");
        fprintf(io_client, "404 Not Found\r\n");
    } else {
        printf("[1] INVALID REQUEST\n");
        printf("[1] REPLYING TO CLIENT REQUEST (400 Bad Request)\n");
        fprintf(io_client, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(io_client, "Connection: close\r\n");
        fprintf(io_client, "Content-Length: 17\r\n");
        fprintf(io_client, "\r\n");
        fprintf(io_client, "400 Bad Request\r\n");
    }

    fflush(io_client);
    /*
    do {
        fgets(buffer_line, HTTP_LINE_LENGTH, io_client);
        line_length = strlen(buffer_line);
        //printf("Length: %ld\n", line_length);
        printf("Received:\n%s\n", buffer_line);
        //fprintf(io_client, "<Pawnee>%s\n", line);
        //fflush(io_client);
    } while (line_length > 1);
    */
    

    free(io_client);
}

void skip_header(FILE* io_client) {
    char buffer_line[HTTP_LINE_LENGTH];
    while (strcmp("\r\n", fgets_or_exit(buffer_line, HTTP_LINE_LENGTH, io_client)) != 0) {
        printf("[2] HEADER LINE | %s", buffer_line);
    }
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