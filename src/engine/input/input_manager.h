#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "input_keyboard_state.h"

typedef struct {
    KeyboardState keyboard_state;
  //MouseState mouse_state;
} InputManager;

/**
 * @brief Initializes the input manager.
 * @return A pointer to the input manager if success, NULL otherwise.
 */
InputManager* input_manager_init();

/**
 * @brief Destroys the input manager.
 * @param input_manager The input manager.
 */
void input_manager_destroy(InputManager* input_manager);

/**
 * @brief Prepare for update the input manager.
 * @param input_manager The input manager.
 */
void input_manager_prepare_update(InputManager* input_manager);

/**
 * @brief Poll input and return the quit status.
 * @param input_manager The input manager.
 * @return The quit status.
 */
bool input_manager_poll_inputs(InputManager* input_manager);

/**
 * @brief Get the keyboad state.
 * @param input_manager The input manager.
 * @return The keyboard state.
 * @note The keyboard state is updated by input_manager_update().
 */
KeyboardState* input_manager_get_keyboard_state(InputManager* input_manager);

#endif // INPUT_MANAGER_H
