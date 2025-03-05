#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_opengl.h>

typedef struct {
    SDL_Window* sdl_window;
    SDL_GLContext sdl_context;
    const char* title;

    double previous_seconds;
    double current_seconds;
    int frame_count;
} Window;

/**
 * @brief Initializes the window.
 * @param x_pos The x position of the window.
 * @param y_pos The y position of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param title The title of the window.
 * @param fullscreen Whether the window is fullscreen or not.
 * @return A pointer to the window.
 */
Window* window_init(int x_pos, int y_pos, int width, int height, const char* title, bool fullscreen);

/**
 * @brief Swaps the window's back buffer with the front buffer.
 * @param window A pointer to the window.
 */
void window_swap_buffers(Window* window);

/**
 * @brief Clean the window.
 * @param window A pointer to the window.
 */
void window_clean(Window* window);

/**
 * @brief Clear the window.
 * @param window A pointer to the window.
 */
void window_clear(Window* window);


/**
 * @brief Frees the memory allocated for the window.
 * @param window A pointer to the window.
 */
void window_destroy(Window* window);

/**
 * @brief Update the FPS counter.
 * @param window A pointer to the window.
 * @param fps The FPS to display.
 */
void window_update_fps(Window* window, long fps);

#endif
