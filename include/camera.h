#ifndef _CAMERA_H
#define _CAMERA_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>

#include <geometry.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FOV_DEGREES 90.0f
#define MINDIST 1.0f
#define MAXDIST 10.0f
#define ASPECT 800.0f / 600.0f

typedef struct {
    vec3_t pos;
    vec3_t lookAt;
    vec3_t up;

    mat4_t view;
    mat4_t proj;
} camera_t;

camera_t* make_camera(vec3_t, vec3_t, vec3_t);
void delete_camera(camera_t*);
void update_camera(camera_t*);
int camera_bind_shader(camera_t*, GLuint);

#ifdef __cplusplus
}
#endif

#endif