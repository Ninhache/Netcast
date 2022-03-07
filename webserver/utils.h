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
 * @param size Taille du fichier lu
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
 * @param maximum_size La taille maximum du buffer renvoyé (0 : pas de limite)
 * @return La ligne lue terminée par '\\0'
 */
char* read_line_limited (FILE* file, size_t* size, size_t maximum_size);

/**
 * @brief Lis le contenu d'une ligne ou quitte le processus si la lecture échoue
 * @param buffer Zone mémoire qui va recevoir le résultat de la lecture
 * @param size Taille maximum de la ligne à lire
 * @param stream Flux d'entrée/sortie source
 * @return char* 
 */
char* fgets_or_exit(char* buffer, int size, FILE* stream);

#endif