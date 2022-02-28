#ifndef __MAIN_H__
#define __MAIN_H__

/**
 * @brief Exécute le traitement de la socket cliente dans un processus dédié (appel non bloquant)
 * @param client_socket La socket client avec laquelle communiquer
 */
void creer_processus_client(int client_socket);

/**
 * @brief Permet d'assurer que les signaux serons bien ignorés
 */
void initialiser_signaux(void);

/**
 * @brief Effectue un traitement sur un client
 * @param client_socket La socket client avec laquelle communiquer
 */
void traitement_client (int client_socket);
/**
 * @brief Traite le signal et ferme le processus qui a generé l'erreur associé
 * 
 */
void traitement_signal(int sig);

/**
 * @brief Consomme toutes les lignes d'entête jusqu'à arriver au début du corps de la requête
 * @param io_client Descripteur de fichier pour la réception des données
 */
void skip_header(FILE* io_client);

#endif