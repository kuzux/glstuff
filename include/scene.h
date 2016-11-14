#ifndef _SCENE_H
#define _SCENE_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    char objfile[255];
    
    char vshader[255];
    char fshader[255];
} scene_t;

scene_t* make_scene();

int read_from_file(scene_t*, const char*);

void delete_scene(scene_t*);

#ifdef __cplusplus
}
#endif

#endif
