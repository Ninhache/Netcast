#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "utils.h"

#define MAX_LINE_MEMSIZE 100000

char* read_file(char* path, size_t* size) {
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

char* read_line(FILE* file, size_t* size) {
    size_t length = 0;
    int data_read = 0;

    size_t buffer_size = BUFFER_SIZE;
    char* buffer = malloc(sizeof(char) * buffer_size);
    if (buffer == NULL) {
        perror("malloc");
        free(buffer);
        return NULL;
    }

    // Si le caractère lu n'est ni une nouvelle ligne, ni la fin du fichier
    while ((data_read = fgetc(file)) != '\n' && data_read != EOF) {
        // Si le buffer est plein, on l'agrandit (doubler la capacité)
        if (length >= buffer_size) {
            buffer_size = buffer_size + BUFFER_SIZE;
            char* tmp = realloc(buffer, buffer_size);
            if (tmp == NULL) {
                perror("malloc");
                free(tmp);
                return NULL;
            }
            buffer = tmp;
        }

        buffer[length++] = data_read;
    }

    buffer = realloc(buffer, ++length);
    buffer[length - 1] = '\0';

    *size = length;
    return buffer;
}