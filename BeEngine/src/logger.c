#include "logger.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char logger_logPath[256];
FILE *logger_logFile;

void logger_init(const char *filePath) {
    strcpy(logger_logPath, filePath);
    logger_logFile = fopen(logger_logPath, "w+");

    LOG("Logger initialized. Log path: \"%s\"", realpath(logger_logPath, NULL));
}

void logger_log(LogType type, const char *message, ...) {
    char buffer[256], timeBuffer[16];
    time_t now = time(NULL);
    struct tm tm_now;

    va_list args;
    va_start(args, message);

    localtime_r(&now, &tm_now);
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &tm_now);

    switch (type) {
        case LOG_INFO:
            snprintf(buffer, 256, "%s - [INFO] ", timeBuffer);
            break;

        case LOG_WARNING:
            snprintf(buffer, 256, "%s - [WARNING] ", timeBuffer);
            break;

        case LOG_ERROR:
            snprintf(buffer, 256, "%s - [ERROR] ", timeBuffer);
    }

    printf("%s", buffer);
    fprintf(logger_logFile, "%s", buffer);

    vprintf(message, args);
    vfprintf(logger_logFile, message, args);
    va_end(args);

    fprintf(logger_logFile, "\n");
    printf("\n");

    fflush(logger_logFile);
}

// TODO: Clean up logger
void logger_stop() {
    fclose(logger_logFile);
}