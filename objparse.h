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

void parse_string(const char**, int, GLfloat**, GLuint**);

#ifdef __cplusplus
}
#endif

#endif