#ifndef _OBJPARSE_H
#define _OBJPARSE_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define DATAPT_PER_VERTEX 8

void parse_string(const char**, int, GLfloat**, GLuint**);
int parse_file(const char* filename, GLfloat**, GLuint**);

#ifdef __cplusplus
}
#endif

#endif