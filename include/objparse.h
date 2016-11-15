#ifndef _OBJPARSE_H
#define _OBJPARSE_H

#ifdef __cplusplus
extern "C" {
#endif

#define DATAPT_PER_VERTEX 8

typedef struct {
    const char* filename;

    const char* texture_file;
    const char* mtl_file;
    
    char* vertex_shader;
    char* fragment_shader;

    float* vertices;
    int num_vertices;

    unsigned int* faces;
    int num_faces;
} obj_file_t;

obj_file_t* make_obj_file(const char*);

void parse_obj_lines(const char**, int, obj_file_t*);
int parse_obj_file(obj_file_t*);

void delete_obj_file(obj_file_t*);

#ifdef __cplusplus
}
#endif

#endif