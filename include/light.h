#ifndef _LIGHT_H
#define _LIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <geometry.h>

typedef struct {
    vec3_t position, color;
    float power;
} light_t;

light_t* make_light(vec3_t, vec3_t, float);
void delete_light(light_t*);

#ifdef __cplusplus
}
#endif

#endif
