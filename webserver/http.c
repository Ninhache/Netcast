#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "http.h"
#include "utils.h"
#include "logger.h"

void skip_header(FILE* io_client) {
    char buffer_line[HTTP_LINE_LENGTH];
    while (strcmp("\r\n", fgets_or_exit(buffer_line, HTTP_LINE_LENGTH, io_client)) != 0) {
        printf("[2] HEADER LINE | %s", buffer_line);
    }
}

char* rewrite_target(char *target) {
    char* res = malloc(sizeof(char) * strlen(target));
    int i = 0;
    while(*target != '?' && *target != '\0') {
        res[i] = *target;
        i++;
        target++;
    }
    res = realloc(res, i +1);
    res[i+1] = '\0';
    return res;
}

FILE* check_and_open(const char *target, const char *document_root) {
    char request[100];
    sprintf(request, "%s%s", document_root, target);
    FILE* file = fopen(request, "r");
    if(file == NULL) {
        return NULL;
    } else {
        return file;
    }
}


char *get_mime(char *filename) {
    char *ext = strrchr(filename, '.');
    if (ext == NULL) {
        return DEFAULT_MIME_TYPE;
    }
    
    ext++;

    strlower(ext);

    if (strcmp(ext, "html") == 0 || strcmp(ext, "htm") == 0) { return "text/html"; }
    if (strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) { return "image/jpg"; }
    if (strcmp(ext, "css") == 0) { return "text/css"; }
    if (strcmp(ext, "js") == 0) { return "application/javascript"; }
    if (strcmp(ext, "json") == 0) { return "application/json"; }
    if (strcmp(ext, "txt") == 0) { return "text/plain"; }
    if (strcmp(ext, "gif") == 0) { return "image/gif"; }
    if (strcmp(ext, "png") == 0) { return "image/png"; }

    return DEFAULT_MIME_TYPE;
}