#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

#define MAX_LINE_MEMSIZE 8192
#define BUFFER_SIZE 4096

char* read_file (char* path, size_t* size) {
    int file;
    int buffer_size = BUFFER_SIZE;

    char* result = malloc(buffer_size);
    if (result == NULL) {
        perror("malloc");
        free(result);
        return NULL;
    }

    int total_read = 0;

    if ((file = open(path, O_RDONLY)) != -1) {
        int size_read = 0;

        while ((size_read = read(file, result + total_read, buffer_size)) > 0) {
            buffer_size = buffer_size + BUFFER_SIZE;
            if (buffer_size > MAX_LINE_MEMSIZE) {
                perror("buffer size exceeded");
                free(result);
                return NULL;
            }

            total_read += size_read;
            
            char* tmp = realloc(result, buffer_size + total_read);
            if (tmp == NULL) {
                perror("malloc");
                free(tmp);
                return NULL;
            }

            result = tmp;
        }
    }

    close(file);
    result = realloc(result, total_read);
    *size = total_read;
    return result;
}

char* fgets_or_exit(char* buffer, int size, FILE* stream) {
    if (fgets(buffer, size, stream) == NULL) {
        exit(EXIT_SUCCESS);
    }
    return buffer;
}