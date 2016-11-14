#include <jansson.h>
#include <scene.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

scene_t* make_scene() {
    scene_t* res = (scene_t*)malloc(sizeof(scene_t));

    return res;
}

int read_from_file(scene_t* scn, const char* filename) {
    FILE* f = fopen(filename, "r");

    if(!f) {
        printf("Error opening file. errno %d\n", errno);
        return 1;
    }

    json_t* root;
    json_error_t error;

    root = json_loadf(f, 0, &error);

    if(!root) {
        printf("JSON parsing error\n");
        return 1;
    }

    if(!json_is_object(root)) {
        printf("JSON parsing error\n");
        return 1;
    }

    return 0;
}

void delete_scene(scene_t* scn) {
    free(scn);
}