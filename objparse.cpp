#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "objparse.h"

void parse_string(const char** lines, int num_lines, GLfloat** vertices, GLuint** faces) {
    // find the number of vertices and faces we'll need
    int num_vertices = 0;
    int num_faces = 0;

    for(int i=0; i < num_lines; i++) {

    }

    *vertices = (GLfloat*)malloc(num_vertices*sizeof(GLfloat));
    *faces    = (GLuint*)malloc(num_vertices*sizeof(GLuint));
}
