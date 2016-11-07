#ifndef _OBJECT_H
#define _OBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>

#include <objparse.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_VERTICES 10000
#define MAX_FACES 50000

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

    // represents the vertices of the object
    // format: position normals texcoords
    // x y z x y z u v
    GLfloat* vertices;
    int num_vertices;

    // indexed faces
    GLuint* faces;
    int num_faces;
} object_t;

object_t* make_object();
int init_from_obj_file(object_t*, obj_file_t*);

int compile_shaders(object_t*);
int link_shaders(object_t*);
int load_texture(object_t*, const char*);
int bind_data_to_shaders(object_t*);

void object_update(object_t*, SDL_Event, uint64_t);

void bind_buffers(object_t*);
void object_draw(object_t*);

void delete_object(object_t*);

#ifdef __cplusplus
}
#endif

#endif
