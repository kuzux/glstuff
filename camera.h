#ifndef _CAMERA_H
#define _CAMERA_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>

#ifdef __cplusplus
extern "C" {
#endif

#define FOV_DEGREES 45.0f
#define MINDIST 1.0f
#define MAXDIST 10.0f
#define ASPECT 800.0f / 600.0f

typedef struct {
    glm::vec3 pos;
    glm::vec3 lookAt;
    glm::vec3 up;

    glm::mat4 view;
    glm::mat4 proj;
} camera_t;

camera_t* new_camera(glm::vec3, glm::vec3, glm::vec3);
void destroy_camera(camera_t*);
void update_camera(camera_t*);
void camera_bind_shader(camera_t*, GLuint);

#ifdef __cplusplus
}
#endif

#endif