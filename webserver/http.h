#ifndef HTTP_H
#define HTTP_H

// CONSTANTS
#define BUFFER_SIZE 1024
#define HTTP_LINE_LENGTH 8192

#define DEFAULT_MIME_TYPE "application/octet-stream"

/**
 * @brief Permet de passer le header d'un client.
 * @param io_client Le client en question
 */
void skip_header(FILE* io_client);

/**
 * @brief Transforme une URI qui possède des paramètres, en URI qui n'en possède pas
 * @param target La query qui doit être retournée simplfiée
 * @return Une query sans paramètres
 */
char* rewrite_target(char *target);

/**
 * @brief Vérifie si un fichier est disponible dans l'arborescence passée en paramètres
 * @param target Fichier à localiser dans la racine
 * @param document_root Racine du serveur
 * @return Renvoie le fichier si il a été trouvé, NULL sinon
 */
FILE* check_and_open(const char *target, const char *document_root);

#endif