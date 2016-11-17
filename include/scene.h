#ifndef _SCENE_H
#define _SCENE_H

#include <light.h>
#include <camera.h>
#include <objparse.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    char* name;
    char* version;
    const char* filename;

    obj_file_t** objects;
    int num_objects;

    light_t* light;
    camera_t* camera;
} scene_t;

scene_t* make_scene(const char*);

int parse_scene_file(scene_t*);

void delete_scene(scene_t*);

#ifdef __cplusplus
}
#endif

#endif
