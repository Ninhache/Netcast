#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "client.h"
#include "http.h"
#include "http_parse.h"
#include "utils.h"
#include "logger.h"
#include "mimetype.h"

void traitement_client (int client_socket) {
    FILE* io_client = fdopen(client_socket, "a+");

    // Traitement de la reqûete HTTP
    char buffer_line[HTTP_LINE_LENGTH];
    fgets_or_exit(buffer_line, HTTP_LINE_LENGTH, io_client);

    c_log(level2, "Asked for :", buffer_line);
    
    http_request http_req;
    int parsed_req = parse_http_request(buffer_line, &http_req);
    char* target = rewrite_target(http_req.target);

    if (parsed_req == -1) {
        c_log(level4, "Invalid request", target);
        if (http_req.method == HTTP_UNSUPPORTED) {
            c_log(level4, "Invalid request", "Method Not Allowed");
            send_text_response(io_client, 405, "Method Not Allowed", "Method Not Allowed\r\n"); 
        } else {
            c_log(level4, "Invalid request", "Bad Request");
            send_text_response(io_client, 400, "Bad Request", "Bad request\r\n");
        } 
    } else {
        c_log(level1, "Request supported", "...");

        if(strcmp(target,"/") == 0) target = "/index.html";
        
        FILE* file = check_and_open(target, document_root);

        if (file == NULL) {
            c_log(level4, "Request Not Found :", target);
            send_text_response(io_client, 404, "Not Found", "Not Found\r\n");
        } else {
            c_log(level4, "Request Found :", target);
            size_t content_size;
            char* file_content = read_file_ptr(file, &content_size);
            
            
            char* mime = mimetype(target);
            
            send_better_response(io_client, 200, "OK", file_content, mime, content_size);
            
            free(file_content);
            free(mime);
        } 
        fclose(file);
    }   

    c_log(level2, "Client disconncted", "See ya later !");
    fflush(io_client);
    free(io_client);
}

void send_status(FILE* client, int code, const char* reason_phrase) {
    c_log(level1, "Sending response status", "");
    
    char codeNumber[4];
    sprintf(codeNumber, "%d", code);
    s_log(level2, codeNumber, (char*) reason_phrase);

    fprintf(client, "HTTP/1.1 %d %s\r\n", code, reason_phrase);
}

void send_text_response(FILE *client, int code, const char *reason_phrase, const char *message_body) {
    send_better_response(client, code, reason_phrase, message_body, "text/plain", strlen(message_body));
}

void send_better_response(FILE *client, int code, const char *reason_phrase, const char *message_body, char* content_type, size_t size) {
    send_status(client, code, reason_phrase);
    
    c_log(level1, "Sending response content", "");
    //fprintf(client, "Content-Length: %ld\r\n", size);
    //fprintf(client, "Content-Type: %s\r\n", content_type);
    //fprintf(client, "\r\n");
    //fprintf(client, "%s\r\n", message_body);
    
    fprintf(client, "Content-Length: %ld\r\n", size);
    fprintf(client, "Content-Type: %s\r\n", content_type);
    fprintf(client, "\r\n");
    //fprintf(client, "%s\r\n", message_body);
    
    fwrite(message_body, sizeof(char), size, client);
    fflush(client);
}