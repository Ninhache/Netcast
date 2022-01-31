#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * Permet de lire un fichier et d'en récupérer son contenu, et sa taille
 * @param path Fichier à lire
 * @param size taille du fichier lu
 * @return le contenu intégral du fichier
 */
char* read_file(char* path, int* size);

#endif