#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


#include "utils.h"
#include "socket.h"

#define UNUSED(x) (void)(x)


int main(int argc, char **argv) {
    
    UNUSED(argc);
    UNUSED(argv);
    
    int socket_serveur = creer_serveur(8080);
    int welcome_length = -1; 
    const char *message_bienvenue = read_file("./webserver/messageBienvenue.netcast", &welcome_length);

    while (1) {
        
        int socket_client = accept(socket_serveur, NULL, NULL);
    
        if (socket_client == -1) {
            perror("accept client_socket");
            continue;
        }

        write(socket_client, message_bienvenue, welcome_length);

        
        // 3.2
        int i = 0;
        while(i < 10) {            
            write(socket_client, message_bienvenue, welcome_length);
            sleep(1);
            i++;
        }
        

        // fflush(socket_client) ???
        // close(socket_client) ??? [+ perror]
    }

    return EXIT_SUCCESS;
}
