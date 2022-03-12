#ifndef CLIENT_H
#define CLIENT_H

/**
 * @brief Effectue un traitement sur un client
 * @param client_socket La socket client avec laquelle communiquer
 */
void traitement_client (int client_socket);

/**
 * @brief Transmet au client une ligne de status correspondant aux paramètres de la fonctions
 * @param client Le client qui recevera la ligne de status
 * @param code Le code status de retour du serveur
 * @param reason_phrase La phrase associé au code erreur
 */
void send_status(FILE* client, int code, const char* reason_phrase);

/**
 * @brief Répond au client en fonctions des paramètres
 * @param client Le client qui recevera la ligne de status
 * @param code Le code status de retour du serveur
 * @param reason_phrase La phrase associé au code erreur
 * @param message_body 
 */
void send_text_response(FILE* client, int code, const char* reason_phrase, const char* message_body);

void send_better_response(FILE* client, int code, const char* reason_phrase, const char* message_body, char* content_type, size_t size);

#endif