#ifndef _OBJECT_H
#define _OBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint shader;

    GLuint vShader;
    GLuint fShader;

    GLuint tex;

    // model transformation
    glm::mat4 model;

    // array object
    GLuint vao;

    // vertex buffer object
    GLuint vbo;
    
    // element buffer object
    GLuint ebo;
} object_t;

object_t* new_object();
int compile_shaders(object_t*);
int link_shaders(object_t*);
int load_texture(object_t*);
int bind_data_to_shaders(object_t*);

void object_update(object_t*, SDL_Event, uint64_t);

void bind_buffers(object_t*);
void object_draw(object_t*);

void destroy_object(object_t*);

#ifdef __cplusplus
}
#endif

#endif
