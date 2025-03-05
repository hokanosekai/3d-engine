#ifndef INPUT_KEYBOARD_STATE_H
#define INPUT_KEYBOARD_STATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <stdbool.h>

typedef enum {
    KEY_NONE,
    KEY_JUST_PRESSED,
    KEY_HELD,
    KEY_JUST_RELEASED
} KeyStatus;

typedef struct {
    const Uint8* current_value;
    Uint8 previous_value[SDL_NUM_SCANCODES];
} KeyboardState;

/**
 * @brief Initializes the keyboard state.
 * @param keyboard_state The keyboard state.
 */
int keyboard_state_init(KeyboardState* keyboard_state);

/**
 * @brief Destroys the keyboard state.
 * @param keyboard_state The keyboard state.
 */
void keyboard_state_destroy(KeyboardState* keyboard_state);

/**
 * @brief Updates the keyboard state.
 * @param keyboard_state The keyboard state.
 */
void keyboard_state_update(KeyboardState* keyboard_state);

/**
 * @brief Gets the key status.
 * @param keyboard_state The keyboard state.
 * @param key The key.
 * @return The key status.
 */
KeyStatus keyboard_state_get_key_status(KeyboardState* keyboard_state, SDL_Scancode key);

/**
 * @brief Get the boolean value of the key.
 * @param keyboard_state The keyboard state.
 * @param key The key.
 * @return The boolean value.
 */
bool keyboard_state_get_key_value(KeyboardState* keyboard_state, SDL_Scancode key);

/**
 * @brief Check if the key is up or just released.
 * @param keyboard_state The keyboard state.
 * @param key The key.
 * @return The boolean value.
 */
bool keyboard_state_is_up(KeyboardState* keyboard_state, SDL_Scancode key);

/**
 * @brief Check if the key is down or just pressed.
 * @param keyboard_state The keyboard state.
 * @param key The key.
 * @return The boolean value.
 */
bool keyboard_state_is_down(KeyboardState* keyboard_state, SDL_Scancode key);

/**
 * @brief Check if the key is just pressed.
 * @param keyboard_state The keyboard state.
 * @param key The key.
 * @return The boolean value.
 */
bool keyboard_state_is_just_pressed(KeyboardState* keyboard_state, SDL_Scancode key);

/**
 * @brief Check if the key is just released.
 * @param keyboard_state The keyboard state.
 * @param key The key.
 * @return The boolean value.
 */
bool keyboard_state_is_just_released(KeyboardState* keyboard_state, SDL_Scancode key);

/**
 * @brief Check if the key is held and not just pressed.
 * @param keyboard_state The keyboard state.
 * @param key The key.
 * @return The boolean value.
 */
bool keyboard_state_is_held(KeyboardState* keyboard_state, SDL_Scancode key);

/**
 * @brief Check if the key is up and not just released.
 * @param keyboard_state The keyboard state.
 * @param key The key.
 * @return The boolean value.
 */
bool keyboard_state_is_free(KeyboardState* keyboard_state, SDL_Scancode key);

#endif // INPUT_KEYBOARD_STATE_H
