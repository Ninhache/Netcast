#ifndef __UTILS_H__
#define __UTILS_H__

// MACRO
#define UNUSED(x) (void)(x)

/**
 * @brief Permet de lire un fichier et d'en récupérer son contenu, et sa taille
 * @param path Fichier à lire
 * @param size Taille du fichier lu
 * @return le contenu intégral du fichier
 */
char* read_file (char* path, size_t* size);

/**
 * @brief Lis le contenu d'une ligne ou quitte le processus si la lecture échoue
 * @param buffer Zone mémoire qui va recevoir le résultat de la lecture
 * @param size Taille maximum de la ligne à lire
 * @param stream Flux d'entrée/sortie source
 * @return char* 
 */
char* fgets_or_exit(char* buffer, int size, FILE* stream);

#endif