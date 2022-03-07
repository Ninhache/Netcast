#ifndef __UTILS_H__
#define __UTILS_H__

// MACRO
#define UNUSED(x) (void)(x)

// CONSTANTS
#define BUFFER_SIZE 1024
#define HTTP_LINE_LENGTH 8192

/**
 * @brief Permet de lire un fichier et d'en récupérer son contenu, et sa taille
 * @param path Fichier à lire
 * @param size taille du fichier lu
 * @return le contenu intégral du fichier
 */
char* read_file (char* path, size_t* size);

/**
 * @brief Permet de lire la prochaine ligne d'un flux de fichier
 * @param file Le pointeur de fichier à lire
 * @param size Le pointeur qui recevra la taille de la chaine retournée
 * @return La ligne lue terminée par '\\0'
 */
char* read_line (FILE* file, size_t* size);

/**
 * @param file Le pointeur de fichier à lire
 * @param size Le pointeur qui recevra la taille de la chaine retournée
 * @param maximum_size la taille maximum du buffer renvoyé (0 : pas de limite)
 * @return La ligne lue terminée par '\\0'
 */
char* read_line_limited (FILE* file, size_t* size, size_t maximum_size);

#endif