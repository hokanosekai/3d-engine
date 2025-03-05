#include <stdio.h>
#include <stdlib.h>

#include "log.h"

// Global variables
Log* LOGGER = NULL;

int log_init(LogLevel level)
{
    LOGGER = malloc(sizeof(Log));
    if (LOGGER == NULL) return -1;

    LOGGER->file = fopen(LOG_FILE, "a");

    return 0;
}

void log_destroy()
{
    fclose(LOGGER->file);
    free(LOGGER);
}

char* log_get_level_string(LogLevel level)
{
    switch (level) {
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
        case LOG_LEVEL_INFO:
            return "INFO";
        case LOG_LEVEL_WARN:
            return "WARN";
        case LOG_LEVEL_ERROR:
            return "ERROR";
        case LOG_LEVEL_FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}

void log_write(LogLevel level, const char *message)
{
    fprintf(LOGGER->file, "[%s] >> %s\n", log_get_level_string(level), message);
    fflush(LOGGER->file);
    printf("[%s] >> %s\n", log_get_level_string(level), message);
}

void LOG(LogLevel level, const char *message) {
    if (level >= LOGGER->level) {
        log_write(level, message);
    }
}

