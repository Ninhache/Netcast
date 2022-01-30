#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * Permet de lire un fichier et d'en récupérer son contenu, et sa taille
 * 
 * @param _fichier Fichier à lire
 * @param _size taille du fichier lu
 * @return le contenu intégral du fichier
 */
char* read_file(char* _fichier, int* _size);

#endif