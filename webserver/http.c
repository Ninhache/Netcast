#include <stdio.h>
#include <string.h>

#include "http.h"
#include "utils.h"

void skip_header(FILE* io_client) {
    char buffer_line[HTTP_LINE_LENGTH];
    while (strcmp("\r\n", fgets_or_exit(buffer_line, HTTP_LINE_LENGTH, io_client)) != 0) {
        printf("[2] HEADER LINE | %s", buffer_line);
    }
}