#include "maths.h"

float random_float()
{
    return (float)rand() / (float)RAND_MAX;
}

void random_axis(float* axis)
{
    axis[0] = random_float() * 2.0f - 1.0f; // Random value between -1 and 1
    axis[1] = random_float() * 2.0f - 1.0f;
    axis[2] = random_float() * 2.0f - 1.0f;

    // Normalize the axis
    float length = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
    axis[0] /= length;
    axis[1] /= length;
    axis[2] /= length;
}

void create_rotation_matrix(float angle, float* matrix)
{
    float radians = angle * (3.14159265359f / 180.0f); // Convert degrees to radians
    float cosA = cos(radians);
    float sinA = sin(radians);

    // 4x4 rotation matrix around the Y-axis
    matrix[0] = cosA;  matrix[4] = 0.0f; matrix[8]  = -sinA; matrix[12] = 0.0f;
    matrix[1] = 0.0f;  matrix[5] = 1.0f; matrix[9]  = 0.0f;  matrix[13] = 0.0f;
    matrix[2] = sinA;  matrix[6] = 0.0f; matrix[10] = cosA;  matrix[14] = 0.0f;
    matrix[3] = 0.0f;  matrix[7] = 0.0f; matrix[11] = 0.0f;  matrix[15] = 1.0f;
}

void create_rotation_matrix_axis(float angle, float* axis, float* matrix)
{
    float radians = angle * (3.14159265359f / 180.0f); // Convert degrees to radians
    float c = cos(radians);
    float s = sin(radians);
    float t = 1.0f - c;

    float x = axis[0], y = axis[1], z = axis[2];

    // First row
    matrix[0] = t * x * x + c;
    matrix[1] = t * x * y - s * z;
    matrix[2] = t * x * z + s * y;
    matrix[3] = 0.0f;

    // Second row
    matrix[4] = t * x * y + s * z;
    matrix[5] = t * y * y + c;
    matrix[6] = t * y * z - s * x;
    matrix[7] = 0.0f;

    // Third row
    matrix[8] = t * x * z - s * y;
    matrix[9] = t * y * z + s * x;
    matrix[10] = t * z * z + c;
    matrix[11] = 0.0f;

    // Fourth row
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void create_perspective_matrix(float fov, float aspect, float near, float far, float* matrix) 
{
    float f = 1.0f / tan(fov * (3.14159265359f / 360.0f)); // Convert fov to radians and calculate cotangent
    matrix[0] = f / aspect; matrix[4] = 0.0f; matrix[8]  = 0.0f;                      matrix[12] = 0.0f;
    matrix[1] = 0.0f;       matrix[5] = f;    matrix[9]  = 0.0f;                      matrix[13] = 0.0f;
    matrix[2] = 0.0f;       matrix[6] = 0.0f; matrix[10] = (far + near) / (near - far); matrix[14] = (2.0f * far * near) / (near - far);
    matrix[3] = 0.0f;       matrix[7] = 0.0f; matrix[11] = -1.0f;                     matrix[15] = 0.0f;
}

void create_view_matrix(float* matrix) 
{
    // Camera position
    float eyeX = 0.0f, eyeY = 0.0f, eyeZ = 4.0f; // Camera is at (0, 0, 3)
    float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f; // Looking at the origin
    float upX = 0.0f, upY = 1.0f, upZ = 0.0f; // Up vector

    // Calculate view matrix
    float f[3] = { centerX - eyeX, centerY - eyeY, centerZ - eyeZ };
    float fLength = sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
    f[0] /= fLength; f[1] /= fLength; f[2] /= fLength;

    float s[3] = { f[1] * upZ - f[2] * upY, f[2] * upX - f[0] * upZ, f[0] * upY - f[1] * upX };
    float sLength = sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
    s[0] /= sLength; s[1] /= sLength; s[2] /= sLength;

    float u[3] = { s[1] * f[2] - s[2] * f[1], s[2] * f[0] - s[0] * f[2], s[0] * f[1] - s[1] * f[0] };

    matrix[0] = s[0]; matrix[4] = s[1]; matrix[8]  = s[2]; matrix[12] = -eyeX * s[0] - eyeY * s[1] - eyeZ * s[2];
    matrix[1] = u[0]; matrix[5] = u[1]; matrix[9]  = u[2]; matrix[13] = -eyeX * u[0] - eyeY * u[1] - eyeZ * u[2];
    matrix[2] = -f[0]; matrix[6] = -f[1]; matrix[10] = -f[2]; matrix[14] = eyeX * f[0] + eyeY * f[1] + eyeZ * f[2];
    matrix[3] = 0.0f; matrix[7] = 0.0f; matrix[11] = 0.0f; matrix[15] = 1.0f;
}

void multiply_matrices(float* a, float* b, float* result) 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i * 4 + j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                result[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
            }
        }
    }
}