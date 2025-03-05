#ifndef MATHS_H
#define MATHS_H

#include <math.h>
#include <stdlib.h>

/**
 * @brief Generate a random float between 0 and 1
 * @return The generated float
 */
float random_float();

/**
 * @brief Generate a random axis
 * @param axis The axis to store the result
 * @note The axis will be normalized
 */
void random_axis(float* axis);

/**
 * @brief Create a rotation matrix
 * @param angle The angle to rotate
 * @param matrix The matrix to store the result
 */
void create_rotation_matrix(float angle, float* matrix);

/**
 * @brief Create a rotation matrix around an axis
 * @param angle The angle to rotate
 * @param axis The axis to rotate around
 * @param matrix The matrix to store the result
 */
void create_rotation_matrix_axis(float angle, float* axis, float* matrix);

/**
 * @brief Create a perspective matrix
 * @param fov The field of view
 * @param aspect The aspect ratio
 * @param near The near plane
 * @param far The far plane
 * @param matrix The matrix to store the result
 */
void create_perspective_matrix(float fov, float aspect, float near, float far, float* matrix);

/**
 * @brief Create a view matrix
 * @param matrix The matrix to store the result
 */
void create_view_matrix(float* matrix);

/**
 * @brief Multiply two matrices
 * @param a The first matrix
 * @param b The second matrix
 * @param result The matrix to store the result
 */
void multiply_matrices(float* a, float* b, float* result);

#endif