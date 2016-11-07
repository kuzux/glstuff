#ifndef _MTLPARSE_H
#define _MTLPARSE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char* filename;

    struct { float r, g, b; } ka, kd, ks;
    float ns;
} mtl_file_t;

mtl_file_t* make_mtl_file(const char*);

int parse_mtl_lines(char**, int, mtl_file_t*);
int parse_mtl_file(mtl_file_t*);

void delete_mtl_file(mtl_file_t*);

#ifdef __cplusplus
}
#endif

#endif
