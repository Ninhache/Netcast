#ifndef SIGNALS_H
#define SIGNALS_H

/**
 * @brief Permet d'assurer que les signaux serons bien ignorés
 */
void initialiser_signaux(void);

/**
 * @brief Traite le signal et ferme le processus qui a generé l'erreur associé
 */
void traitement_signal(int sig);

#endif