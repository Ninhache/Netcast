#ifndef __MAIN_H__
#define __MAIN_H__

/**
 * @brief Permet d'assurer que les signaux serons bien ignorés
 */
void initialiser_signaux(void);

/**
 * @brief Exécute le traitement de la socket cliente dans un processus dédié (appel non bloquant)
 * @param client_socket La socket client avec laquelle communiquer
 */
void creer_processus_client(int client_socket);

/**
 * @brief Effectue un traitement sur un client
 * @param client_socket La socket client avec laquelle communiquer
 */
void traitement_client (int client_socket);

#endif