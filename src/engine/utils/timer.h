#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

#define FPS 60
#define FRAME_DELAY 1000 / FPS

typedef struct {
    // The clock time when the timer started in milliseconds
    unsigned int start_frame;

    // Last frame start time in milliseconds
    unsigned int last_frame;

    // Time of the execution of the run loop. Used to cap the frame rate.
    unsigned int frame_time;
} Timer;

/**
 * @brief Initializes the timer.
 * @return A pointer to the timer.
 */
Timer* timer_init();

/**
 * @brief Starts the timer.
 * @param timer A pointer to the timer.
 */
void timer_start(Timer* timer);

/**
 * @brief Computes the time elapsed since the last frame.
 * @param timer A pointer to the timer.
 * @return The time elapsed since the last frame.
 */
unsigned int timer_compute_delta_time(Timer* timer);

/**
 * @brief Delay the execution of the run loop to cap the frame rate, if the frame rate is too high.
 * @param timer A pointer to the timer.
 */
void timer_delay(Timer* timer);

/**
 * @brief Frees the memory allocated for the timer.
 * @param timer A pointer to the timer.
 */
void timer_destroy(Timer* timer);

#endif
