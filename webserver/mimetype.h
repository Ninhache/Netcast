#ifndef MIMETYPE_H
#define MIMETYPE_H

/**
 * @brief Récupère le type MIME d'un fichier
 * @param file_path Chemin du fichier
 * @return char* Un type MIME (application/json, text/html, image/png, ...)
 */
char* mimetype(char *file_path);

/**
 * @brief Récupère le type MIME correspondant à une extension de fichier
 * @param file_path Extension du fichier
 * @return char* Un type MIME (application/json, text/html, image/png, ...)
 */
char* ext_mimetype(char *ext);

#endif