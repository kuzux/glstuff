#include <geometry.h>

vec2_t make_vec2(float x, float y) {
    vec2_t res;

    res.x = x;
    res.y = y;

    return res;
}

vec3_t make_vec3(float x, float y, float z) {
    vec3_t res;

    res.x = x;
    res.y = y;
    res.z = z;

    return res;
}

vec4_t make_vec4(float x, float y, float z, float t) {
    vec4_t res;

    res.x = x;
    res.y = y;
    res.z = z;
    res.t = t;

    return res;
}
