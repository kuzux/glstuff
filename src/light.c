#include <stdlib.h>
#include <light.h>

light_t* make_light(vec3f_t pos, vec3f_t color) {
    light_t* res = (light_t*)malloc(sizeof(light_t));

    res->position = pos;
    res->color = color;

    return res;
}

void delete_light(light_t* l) {
    free(l);
}