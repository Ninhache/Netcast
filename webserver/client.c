#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "http.h"
#include "http_parse.h"
#include "utils.h"

void traitement_client (int client_socket) {
    FILE* io_client = fdopen(client_socket, "a+");

    // Traitement de la reqûete HTTP
    char buffer_line[HTTP_LINE_LENGTH];
    fgets_or_exit(buffer_line, HTTP_LINE_LENGTH, io_client);

    printf("[0] %s", buffer_line);

    
    http_request http_req;

    int parsed_req = parse_http_request(buffer_line, &http_req);

    if (parsed_req == -1) {
        if (http_req.method == HTTP_UNSUPPORTED) {
            send_response(io_client, 405, "Method Not Allowed", "Method Not Allowed\r\n"); 
        } else {
            send_response(io_client, 400, "Bad Request", "Bad request\r\n");
        } 
    } else {
        if (strcmp(http_req.target, "/") == 0) {
            send_response(io_client, 200, "OK", message_bienvenue);
        } else {
            send_response(io_client, 404, "Not Found", "Not Found\r\n");
        }
    }

    /*
    if(strcmp(buffer_line, "GET / HTTP/1.1\r\n") == 0) {
        printf("[1] VALID REQUEST (GET)\n");
        printf("[1] SENDING WELCOME MESSAGE\n");
        printf("[1] PROCESSING HEADER LINES\n");

        while (strcmp("\r\n", fgets(buffer_line, HTTP_LINE_LENGTH, io_client)) != 0) {
            printf("[2] HEADER LINE | %s", buffer_line);
        }

        printf("[1] REPLYING TO CLIENT REQUEST (200 OK)\n");
        fprintf(io_client, "HTTP/1.1 200 OK\r\n");
        fprintf(io_client, "Content-Length: %ld\r\n\r\n", welcome_length);
        fprintf(io_client, "%s\r\n", message_bienvenue);
    } else {
        printf("[1] INVALID REQUEST\n");
        printf("[1] REPLYING TO CLIENT REQUEST (400 Bad Request)\n");
        fprintf(io_client, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(io_client, "Connection: close\r\n");
        fprintf(io_client, "Content-Length: 17\r\n");
        fprintf(io_client, "\r\n");
        fprintf(io_client, "400 Bad Request\r\n");
    }
    */
    

    fflush(io_client);
    free(io_client);
}

void send_status(FILE* client, int code, const char* reason_phrase) {
    fprintf(client, "HTTP/1.1 %d %s\r\n", code, reason_phrase);
}

void send_response(FILE *client, int code, const char *reason_phrase, const char *message_body) {
    send_status(client, code, reason_phrase);
    
    fprintf(client, "Content-Length: %ld\r\n", strlen(message_body));
    fprintf(client, "\r\n");
    fprintf(client, "%s\r\n", message_body);

}