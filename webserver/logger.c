#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "logger.h"

e_level level1;
e_level level2;
e_level level3;
e_level level4;
e_level level5;

void setupLogger() {
    level1 = INFORMATIONS;
    level2 = MINOR;
    level3 = IMPORTANT;
    level4 = MAJOR;
    level5 = SUCCESS;
}

void setColor(e_level level, char** begin, char** end) {
    switch (level) {
        case INFORMATIONS:
            *begin = LOG_WHITE;
            break;
        case MINOR:
            *begin = LOG_YELLOW;
            break;
        case IMPORTANT:
            *begin = LOG_BLUE;
            break;
        case MAJOR:
            *begin = LOG_RED;
            break;
        case SUCCESS:
            *begin = LOG_GREEN;
            break;
    }
    *end = LOG_RESET;
}

void s_log(e_level level, char* messageTitle, char* messageBody) {
    char* errorBegin;
    char* errorEnd;
    setColor(level, &errorBegin, &errorEnd);

    printf("%s[SERVER] : %s %s %s\n", errorBegin, messageTitle, messageBody, errorEnd);
}

void c_log(e_level level, char* messageTitle, char* messageBody) {
    char* errorBegin;
    char* errorEnd;
    setColor(level, &errorBegin, &errorEnd);

    printf("%s[CLIENT %d] : %s %s %s\n", errorBegin, getpid(), messageTitle, messageBody, errorEnd);
}