#ifndef SERVER_H
#define SERVER_H

#define DEFAULT_PORT 8080

/**
 * @brief Démarre le serveur web sur le port spécifié
 * @param port Port du serveur WEB 
 */
void demarrer_serveur(int port);

/**
 * @brief Exécute le traitement de la socket cliente dans un processus dédié (appel non bloquant)
 * @param client_socket La socket client avec laquelle communiquer
 */
void creer_processus_client(int client_socket);

#endif