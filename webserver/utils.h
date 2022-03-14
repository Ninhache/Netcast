#ifndef UTILS_H
#define UTILS_H

// MACRO
#define UNUSED(x) (void)(x)

extern size_t welcome_length;
extern char* message_bienvenue;
extern char* document_root;

/**
 * @brief Permet de lire un fichier et d'en récupérer son contenu, et sa taille
 * @param path Fichier à lire
 * @param size Taille du fichier lu
 * @return le contenu intégral du fichier
 */
char* read_file_path(char* path, size_t* size);

char* read_file_ptr(FILE* file, size_t* size);

/**
 * @brief Lis le contenu d'une ligne ou quitte le processus si la lecture échoue
 * @param buffer Zone mémoire qui va recevoir le résultat de la lecture
 * @param size Taille maximum de la ligne à lire
 * @param stream Flux d'entrée/sortie source
 * @return char* 
 */
char* fgets_or_exit(char* buffer, int size, FILE* stream);

/**
 * @brief Transforme une chaine de charactères en chaîne de charactère minuscule
 * @param string Chaîne de chractère à rendre minuscule
 * @return Renvoie la chaîne de charactère en minuscule
 */
char* strlower(char* string);

/**
 * @brief Récupère l'extension du nom de fichier passé en paramètre
 * @param file_path Chemin du fichier 
 * @return char* Une extension de fichier (sans le point)
 * @example /home/user/file.png -> png
 */
char* file_extension(char *file_path);

#endif