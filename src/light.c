#include <stdlib.h>
#include <light.h>

light_t* make_light(vec3_t pos, vec3_t color, float p) {
    light_t* res = (light_t*)malloc(sizeof(light_t));

    res->position = pos;
    res->color = color;
    res->power = p;

    return res;
}

void delete_light(light_t* l) {
    free(l);
}
