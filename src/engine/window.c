#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>
// #include <GL/glew.h>
#include <stdbool.h>

#include "window.h"
#include "config.h"
#include "utils/log.h"

Window* window_init(int x_pos, int y_pos, int width, int height, const char* title, bool fullscreen)
{
    Window* window = malloc(sizeof(Window));

    if (window == NULL)
    {
        LOG_ERROR("Failed to allocate memory for window.");
        return NULL;
    }

    window->current_seconds = 0.0;
    window->previous_seconds = 0.0;
    window->frame_count = 0;
    window->sdl_window = NULL;
    window->sdl_context = NULL;
    window->title = NULL;

    int flags = SDL_WINDOW_OPENGL;
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

        // Initialize SDL window
        window->sdl_window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if (window->sdl_window == NULL)
        {
            LOG_ERROR("Failed to create SDL window.");
            LOG_ERROR(SDL_GetError());
            return NULL;
        }

        // Initialize SDL OpenGL context
        window->sdl_context = SDL_GL_CreateContext(window->sdl_window);
        if (window->sdl_context == NULL)
        {
            LOG_ERROR("Failed to create SDL OpenGL context.");
            LOG_ERROR(SDL_GetError());
            return NULL;
        }

        // Enable VSync
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
            LOG_ERROR("Failed to enable VSync.");
            LOG_ERROR(SDL_GetError());
        }

        glViewport(0, 0, width, height);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (glGetError() != GL_NO_ERROR)
        {
            LOG_ERROR("Failed to initialize OpenGL.");
            LOG_ERROR(SDL_GetError());
            return NULL;
        }
    } else {
        LOG_ERROR("Failed to initialize SDL.");
        LOG_ERROR(SDL_GetError());
        return NULL;
    }

    window->title = title;

    return window;
}

void window_swap_buffers(Window *window)
{
    SDL_GL_SwapWindow(window->sdl_window);
}

void window_clear(Window *window)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both color and depth buffers
}

void window_update_fps(Window *window, long delta_time)
{
    double elapsed_seconds;
    window->current_seconds += delta_time / 1000.0;
    elapsed_seconds = window->current_seconds - window->previous_seconds;

    // Limit text updates to 4 per second
    if (elapsed_seconds > 0.25)
    {
        window->previous_seconds = window->current_seconds;
        char tmp[128];
        double fps = window->frame_count / elapsed_seconds;
        sprintf(tmp, "%s - FPS: %.2f", window->title, fps);
        SDL_SetWindowTitle(window->sdl_window, tmp);
        window->frame_count = 0;
    }
    window->frame_count++;
}

void window_destroy(Window *window)
{
    SDL_GL_DeleteContext(window->sdl_context);
    SDL_DestroyWindow(window->sdl_window);
    SDL_Quit();
}


















