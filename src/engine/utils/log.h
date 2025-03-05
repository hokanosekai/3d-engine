#ifndef LOG_H
#define LOG_H

#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#define LOG_FILE "gl.log"

typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} LogLevel;

typedef struct {
    LogLevel level;
    FILE* file;
} Log;

extern Log* LOGGER;

/**
 * @brief Initializes the log.
 * @param level The log level.
 * @return 0 on success, -1 on failure.
 */
int log_init(LogLevel level);

/**
 * @brief Destroys the log.
 */  
void log_destroy();

/**
 * @brief Get the prefix for the log level.
 * @param level The log level.
 * @return The prefix.
 */
char* log_get_level_string(LogLevel level);

/**
 * @brief Write the message to the log file.
 * @param level The log level.
 * @param message The message.
 */
void log_write(LogLevel level, const char* message);

/**
 * @brief Log the message at the debug level.
 * @param level The log level.
 * @param message The message.
 * @param args The arguments.
 */
void LOG(LogLevel level, const char *message);

#define LOG_DEBUG(message) LOG(LOG_LEVEL_DEBUG, message)
#define LOG_INFO(message) LOG(LOG_LEVEL_INFO, message)
#define LOG_WARN(message) LOG(LOG_LEVEL_WARN, message)
#define LOG_ERROR(message) LOG(LOG_LEVEL_ERROR, message)
#define LOG_FATAL(message) LOG(LOG_LEVEL_FATAL, message)

#endif
