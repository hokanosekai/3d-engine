#include "input_keyboard_state.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <string.h>

int keyboard_state_init(KeyboardState* state)
{
    state = malloc(sizeof(KeyboardState));
    if (state == NULL)
        return -1;

    state->current_value = SDL_GetKeyboardState(NULL);
    memset(state->previous_value, 0, SDL_NUM_SCANCODES);

    return 0;
}

void keyboard_state_destroy(KeyboardState* state)
{
    free(state);
}

void keyboard_state_update(KeyboardState *keyboard_state)
{
    keyboard_state->current_value = SDL_GetKeyboardState(NULL);
    memcpy(keyboard_state->previous_value,
          keyboard_state->current_value,
          SDL_NUM_SCANCODES);
}

KeyStatus keyboard_state_get_key_status(KeyboardState *keyboard_state, SDL_Scancode key)
{
    if (keyboard_state->previous_value[key] == 0) {
        if (keyboard_state->current_value[key] == 0)
            return KEY_NONE;
        else
            return KEY_JUST_PRESSED;
    } else {
        if (keyboard_state->current_value[key] == 0) {
            return KEY_JUST_RELEASED;
        } else {
            return KEY_HELD;
        }
    }
}

bool keyboard_state_get_key_value(KeyboardState *keyboard_state, SDL_Scancode key)
{
    return keyboard_state->current_value[key] != 0;
}

bool keyboard_state_is_up(KeyboardState *keyboard_state, SDL_Scancode key)
{
    return !keyboard_state_get_key_value(keyboard_state, key);
}

bool keyboard_state_is_down(KeyboardState *keyboard_state, SDL_Scancode key)
{
    return keyboard_state_get_key_value(keyboard_state, key);
}

bool keyboard_state_is_free(KeyboardState *keyboard_state, SDL_Scancode key)
{
    return keyboard_state_get_key_status(keyboard_state, key) == KEY_NONE;
}

bool keyboard_state_is_just_pressed(KeyboardState *keyboard_state, SDL_Scancode key)
{
    return keyboard_state_get_key_status(keyboard_state, key) == KEY_JUST_PRESSED;
}

bool keyboard_state_is_just_released(KeyboardState *keyboard_state, SDL_Scancode key)
{
    return keyboard_state_get_key_status(keyboard_state, key) == KEY_JUST_RELEASED;
}

bool keyboard_state_is_held(KeyboardState *keyboard_state, SDL_Scancode key)
{
    return keyboard_state_get_key_status(keyboard_state, key) == KEY_HELD;
}



