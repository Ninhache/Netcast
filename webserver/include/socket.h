#ifndef __SOCKET_H__
#define __SOCKET_H__

/**
 * Instancie une socket serveur écoutant les connexions entrantes sur le port spécifié
 * @param port Port sur lequel écouter les connexions entrantes
 * @return Le numéro de la socket serveur créée ou -1 en cas d'erreur
 */
int creer_serveur(int port);

/**
 * Instancie une socket client connectée à la socket seveur passée en paramètre
 * @param server_socket Socket serveur qui recevra la connexion cliente
 * @return Le numéro de la socket cliente créée ou -1 en cas d'erreur
 */
int creer_client(int server_socket);

#endif