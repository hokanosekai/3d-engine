#include "input_manager.h"
#include "input_keyboard_state.h"
#include <SDL2/SDL_events.h>
#include "../utils/log.h"

InputManager* input_manager_init()
{
    InputManager* input_manager = malloc(sizeof(InputManager));
    if (input_manager == NULL)
        return NULL;

    if (keyboard_state_init(&input_manager->keyboard_state) != 0)
        return NULL;

    return input_manager;
}

void input_manager_destroy(InputManager *input_manager)
{
    keyboard_state_destroy(&input_manager->keyboard_state);
    free(input_manager);
}

void input_manager_prepare_update(InputManager *input_manager)
{
    keyboard_state_update(&input_manager->keyboard_state);
}

bool input_manager_poll_inputs(InputManager *input_manager)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    bool quit = true;
    switch (event.type)
    {
        case SDL_QUIT:
            quit = false;
            break;
        default:
            break;
    }
    return quit;
}

KeyboardState* input_manager_get_keyboard_state(InputManager *input_manager)
{
    return &input_manager->keyboard_state;
}
