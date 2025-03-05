#include "timer.h"
#include "utils/log.h"

Timer* timer_init()
{
    Timer* timer = malloc(sizeof(Timer));
    timer->last_frame = 0;
    timer->frame_time = 0;
    timer->start_frame = 0;
    return timer;
}

void timer_start(Timer* timer)
{
    timer->start_frame = SDL_GetTicks();
}

unsigned int timer_compute_delta_time(Timer *timer)
{
    timer->start_frame = SDL_GetTicks();
    unsigned int delta_time = timer->start_frame - timer->last_frame;
    timer->last_frame = timer->start_frame;
    return delta_time;
}

void timer_delay(Timer *timer)
{
    timer->frame_time = SDL_GetTicks() - timer->start_frame;
    if (timer->frame_time < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - timer->frame_time);
    }
}

void timer_destroy(Timer* timer)
{
    free(timer);
}
