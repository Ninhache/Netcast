#ifndef __UTILS_H__
#define __UTILS_H__

// MACRO
#define UNUSED(x) (void)(x)

// CONSTANTS
#define BUFFER_SIZE 1024

/**
 * @brief Permet de lire un fichier et d'en récupérer son contenu, et sa taille
 * @param path Fichier à lire
 * @param size taille du fichier lu
 * @return le contenu intégral du fichier
 */
char* read_file(char* path, size_t* size);

/**
 * @brief Permet de lire la prochaine ligne d'un flux de fichier
 * @param file Le pointeur de fichier à lire
 * @param size Le pointeur qui recevra la taille de la chaine retournée
 * @return La ligne lue terminée par '\\0'
 */
// TODO: La finction ne veut pas renvoyer de buffer de taille supérieure à 4096 octets
// Réparer ce bug (fread + memcpy ?)
char* read_line(FILE* file, size_t* size);

#endif