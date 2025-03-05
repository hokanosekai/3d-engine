#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "engine/utils/log.h"
#include "engine/input/input_manager.h"
#include "engine/utils/timer.h"
#include "engine/utils/maths.h"
#include "engine/window.h"
#include "engine/config.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int delta_time;

    // Initialize log
    if (log_init(LOG_LEVEL_DEBUG) == -1) {
        printf("[FATAL] >> log_init() failed");
        return EXIT_FAILURE;
    };

    // Initialize timer
    Timer* timer = timer_init();
    if (timer == NULL) {
        LOG_FATAL("timer_init() failed");
        return EXIT_FAILURE;
    }

    // Initialize main window
    Window* window = window_init(WINDOW_X_POS, WINDOW_Y_POS, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);  
    if (window == NULL) {
        LOG_FATAL("window_init() failed");
        return EXIT_FAILURE;
    }

    // Initialize input manager
    InputManager* input_manager = input_manager_init();
    if (input_manager == NULL) {
        LOG_FATAL("input_manager_init() failed");
        return EXIT_FAILURE;
    }

    LOG_INFO("Starting main loop");
    timer_start(timer);

    // Our cube
    GLfloat vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

        // Back face
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,

        // Right face
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,

        // Top face
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    };

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        LOG_ERROR("Failed to initialize GLEW.");
        SDL_GL_DeleteContext(window->sdl_context);
        SDL_DestroyWindow(window->sdl_window);
        free(window);
        return EXIT_FAILURE;
    }

    // Check for OpenGL errors after GLEW initialization
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        LOG_ERROR("OpenGL error after GLEW initialization.");
        SDL_GL_DeleteContext(window->sdl_context);
        SDL_DestroyWindow(window->sdl_window);
        free(window);
        return EXIT_FAILURE;
    }

    // Create VBO and VAO
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Create and compile vertex shaders
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "layout (location = 1) in vec3 normal;\n" // Normales des sommets
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "out vec3 FragPos;\n" // Position du fragment dans l'espace monde
        "out vec3 Normal;\n"  // Normale du fragment
        "void main()\n"
        "{\n"
        "    FragPos = vec3(model * vec4(position, 1.0));\n" // Position dans l'espace monde
        "    Normal = mat3(transpose(inverse(model))) * normal;\n" // Normale transformée
        "    gl_Position = projection * view * model * vec4(position, 1.0);\n"
        "}\0";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile fragment shaders
    const char *fragmentShaderSource = "#version 330 core\n"
        "in vec3 FragPos;\n"
        "in vec3 Normal;\n"
        "out vec4 color;\n"
        "uniform vec3 lightPos;\n"
        "uniform vec3 lightColor;\n"
        "uniform vec3 objectColor;\n"
        "uniform bool lightEnabled;\n" // Ajoutez un uniform pour contrôler l'état de la lumière
        "void main()\n"
        "{\n"
        "    vec3 result;\n"
        "    if (lightEnabled) {\n"
        "        // Réflexion ambiante\n"
        "        float ambientStrength = 0.1;\n"
        "        vec3 ambient = ambientStrength * lightColor;\n"
        ""
        "        // Réflexion diffuse\n"
        "        vec3 norm = normalize(Normal);\n"
        "        vec3 lightDir = normalize(lightPos - FragPos);\n"
        "        float diff = max(dot(norm, lightDir), 0.0);\n"
        "        vec3 diffuse = diff * lightColor;\n"
        ""
        "        // Réflexion spéculaire\n"
        "        float specularStrength = 0.5;\n"
        "        vec3 viewDir = normalize(-FragPos);\n"
        "        vec3 reflectDir = reflect(-lightDir, norm);\n"
        "        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
        "        vec3 specular = specularStrength * spec * lightColor;\n"
        ""
        "        // Résultat final\n"
        "        result = (ambient + diffuse + specular) * objectColor;\n"
        "    } else {\n"
        "        // Si la lumière est désactivée, utilisez uniquement la couleur de l'objet\n"
        "        result = objectColor;\n"
        "    }\n"
        "    color = vec4(result, 1.0);\n"
        "}\0";
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link shaders to a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // glDisable(GL_BACK);

    // Create projection matrix
    float projection_matrix[16];
    float aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
    create_perspective_matrix(45.0f, aspect_ratio, 0.1f, 100.0f, projection_matrix);

    // Create view matrix
    float view_matrix[16];
    create_view_matrix(view_matrix);

    // Pass projection and view matrices to the shader
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection_matrix);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view_matrix);

    // Set light properties
    glUseProgram(shaderProgram);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), 3.0f, 3.0f, 4.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 1.6f, 0.5f, 0.2f);

    bool is_running = true;
    bool is_light_enabled = true; // Light is enabled by default
    bool auto_rotating = false;

    float rotation_axis[3];
    float rotation_speed = 50.0f; // Degrees per second
    float rotation_angle = 50.0f;
    float rotation_angle_x = 0.0f; // Rotation around X-axis
    float rotation_angle_y = 0.0f; // Rotation around Y-axis

    // float axis_change_timer = 0.0f; // Timer to change the rotation axis

    // Add lightEnabled as parameter for shader
    GLint lightEnabledLoc = glGetUniformLocation(shaderProgram, "lightEnabled");
    glUseProgram(shaderProgram);
    glUniform1i(lightEnabledLoc, is_light_enabled);

    // Main loop
    while (is_running) {
        timer_start(timer);
        delta_time = timer_compute_delta_time(timer);

        window_update_fps(window, delta_time);

        // Handle input
        input_manager_prepare_update(input_manager);
        is_running = input_manager_poll_inputs(input_manager);
        KeyboardState* keyboard_state = input_manager_get_keyboard_state(input_manager);

        // Exit
        if (keyboard_state_get_key_status(keyboard_state, SDL_SCANCODE_ESCAPE) == KEY_JUST_PRESSED) {
            LOG_INFO("Escape key pressed");
            is_running = false;
        }

        // Toggle light
        if (keyboard_state_is_just_pressed(keyboard_state, SDL_SCANCODE_L)) {
            LOG_INFO("Light toggled");
            is_light_enabled = !is_light_enabled;
        }

        // Toggle auto rotate
        if (keyboard_state_is_just_pressed(keyboard_state, SDL_SCANCODE_R)) {
            LOG_INFO("Auto rotate toggled");
            auto_rotating = !auto_rotating;

            // Generate a random rotation axis
            random_axis(rotation_axis);
        }

        // Rotate cube with arrow keys
        if (keyboard_state_is_down(keyboard_state, SDL_SCANCODE_LEFT)) {
            rotation_angle_y += rotation_speed * delta_time / 1000.0f;
        }
        if (keyboard_state_is_down(keyboard_state, SDL_SCANCODE_RIGHT)) {
            rotation_angle_y -= rotation_speed * delta_time / 1000.0f;
        }
        if (keyboard_state_is_down(keyboard_state, SDL_SCANCODE_UP)) {
            rotation_angle_x += rotation_speed * delta_time / 1000.0f;
        }
        if (keyboard_state_is_down(keyboard_state, SDL_SCANCODE_DOWN)) {
            rotation_angle_x -= rotation_speed * delta_time / 1000.0f;
        }

        float rotation_matrix[16];

        if (auto_rotating) {
            rotation_angle += rotation_speed * delta_time / 1000.0f;
            if (rotation_angle >= 360.0f) {
                rotation_angle -= 360.0f; // Keep angle within 0-360 degrees
            }

            // Change the rotation axis every 5 seconds
            // axis_change_timer += delta_time / 1000.0f;
            // if (axis_change_timer >= 5.0f) {
            //     random_axis(rotation_axis); // Generate a new random axis
            //     axis_change_timer = 0.0f; // Reset the timer
            // }

            create_rotation_matrix_axis(rotation_angle, rotation_axis, rotation_matrix);

        } else {
            // Create rotation matrices
            float rotation_matrix_x[16], rotation_matrix_y[16];
            create_rotation_matrix_axis(rotation_angle_x, (float[]){1.0f, 0.0f, 0.0f}, rotation_matrix_x);
            create_rotation_matrix_axis(rotation_angle_y, (float[]){0.0f, 1.0f, 0.0f}, rotation_matrix_y);
            multiply_matrices(rotation_matrix_x, rotation_matrix_y, rotation_matrix);
        }

        // Pass is_light_enabled to shader
        glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, "lightEnabled"), is_light_enabled);

        // Pass rotation matrix to the shader
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotation_matrix);

        // Clear the screen
        window_clear(window);

        // Render the cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Swap buffers
        window_swap_buffers(window);

        // Delay to maintain frame rate
        timer_delay(timer);
    }

    // Cleanup
    timer_destroy(timer);
    window_destroy(window);
    log_destroy();

    return EXIT_SUCCESS;
}
