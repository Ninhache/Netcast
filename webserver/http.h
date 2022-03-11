#ifndef HTTP_H
#define HTTP_H

// CONSTANTS
#define BUFFER_SIZE 1024
#define HTTP_LINE_LENGTH 8192

/**
 * @brief Permet de passer le header d'un client.
 * @param io_client Le client en question
 */
void skip_header(FILE* io_client);

#endif