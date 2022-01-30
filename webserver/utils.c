#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "utils.h"


char* read_file(char* _fichier, int* _size) {
    int fdFile;
    
    int bufferSize = 100;
    char* res = malloc(bufferSize);
    int total_read = 0;

    if((fdFile = open(_fichier, O_RDONLY)) != -1) {
        
        int sizeReaded = 0;

        while( (sizeReaded=read(fdFile, res + total_read, bufferSize)) > 0 ) {
            bufferSize = bufferSize*2;
            total_read += sizeReaded;
            res = realloc(res, bufferSize + total_read );
        }
    }
    
    close(fdFile);
    res = realloc(res, total_read);
    *_size = total_read;
    return res;
}