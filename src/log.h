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
int log_init(Log* log, LogLevel level);

void log_destroy(Log* log);

void log_restart(Log* log);

char* log_get_level_string(LogLevel level);

void log_write(LogLevel level, const char* message);

void LOG(LogLevel level, const char* message)
{
  if (level >= LOGGER->level) {
    log_write(level, message);
  }
}
