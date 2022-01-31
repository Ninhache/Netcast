#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "utils.h"

#define BUFFER_SIZE 1024

char* read_file(char* path, int* size) {
    int file;
    
    int buffer_size = BUFFER_SIZE;
    char* result = malloc(buffer_size);
    int total_read = 0;

    if ((file = open(path, O_RDONLY)) != -1) {
        int size_read = 0;

        while ((size_read = read(file, result + total_read, buffer_size)) > 0) {
            buffer_size = buffer_size * 2;
            total_read += size_read;
            result = realloc(result, buffer_size + total_read);
        }
    }

    close(file);
    result = realloc(result, total_read);
    *size = total_read;
    return result;
}