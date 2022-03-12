#ifndef LOGGER_H
#define LOGGER_H

#define LOG_RED     "\033[0;31m"
#define LOG_GREEN   "\033[0;32m"
#define LOG_YELLOW  "\033[0;33m"
#define LOG_BLUE    "\033[0;34m"
#define LOG_WHITE   "\033[0;37m"
#define LOG_RESET   "\x1b[0m"

typedef enum {
    INFORMATIONS,
    MINOR,
    IMPORTANT,
    MAJOR,
    SUCCESS
} e_level;

extern e_level level1;
extern e_level level2;
extern e_level level3;
extern e_level level4;
extern e_level level5;


void setupLogger();

void setColor(e_level level, char** begin, char** end);

void s_log(e_level level, char* messageTitle, char* messageBody);

void c_log(e_level level, char* messageTitle, char* messageBody);

#endif