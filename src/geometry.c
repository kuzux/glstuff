#include <math.h>

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

float deg_to_rad(float deg) {
    return M_PI * (deg / 180.0f);
}

vec2_t vec2_num(float n) {
    return make_vec2(n, n);
}

vec3_t vec3_num(float n) {
    return make_vec3(n, n, n);
}

vec4_t vec4_num(float n) {
    return make_vec4(n, n, n, n);
}

mat2_t mat2_zero() {
    mat2_t res;

    for(int i=0;i<4;i++) res.e[i] = 0.0f;

    return res;
}

mat3_t mat3_zero() {
    mat3_t res;

    for(int i=0;i<9;i++) res.e[i] = 0.0f;

    return res;
}

mat4_t mat4_zero() {
    mat4_t res;

    for(int i=0;i<16;i++) res.e[i] = 0.0f;

    return res;
}

mat2_t mat2_unit() {
    mat2_t res = mat2_zero();

    res.e[0] = 1.0f;
    res.e[3] = 1.0f;

    return res;
}

mat3_t mat3_unit() {
    mat3_t res = mat3_zero();

    res.e[0] = 1.0f;
    res.e[4] = 1.0f;
    res.e[8] = 1.0f;

    return res;
}

mat4_t mat4_unit() {
    mat4_t res = mat4_zero();

    res.e[0] = 1.0f;
    res.e[5] = 1.0f;
    res.e[10] = 1.0f;
    res.e[15] = 1.0f; 

    return res;
}

float vec2_length(vec2_t v) {
    
}

float vec3_length(vec3_t v) {

}

float vec4_length(vec4_t v) {

}

vec2_t vec2_invert(vec2_t v) {

}

vec3_t vec3_invert(vec3_t v) {

}

vec4_t vec4_invert(vec4_t v) {

}

vec2_t vec2_add(vec2_t a, vec2_t b) {

}

vec3_t vec3_add(vec3_t a, vec3_t b) {

}

vec4_t vec4_add(vec4_t a, vec4_t b) {

}

vec2_t vec2_multiply(vec2_t v, float c) {

}

vec3_t vec3_multiply(vec3_t v, float c) {

}

vec4_t vec4_multiply(vec4_t v, float c) {

}

float vec2_normalize(vec2_t v) {

}

float vec3_normalize(vec3_t v) {

}

float vec4_normalize(vec4_t v) {

}

float vec2_dot(vec2_t a, vec2_t b) {

}

float vec3_dot(vec3_t a, vec3_t b) {

}

float vec4_dot(vec4_t a, vec4_t b) {

}

float vec2_cross(vec2_t a, vec2_t b) {

}

vec3_t vec3_cross(vec3_t a, vec3_t b) {

}

mat4_t look_at(vec3_t pos, vec3_t look, vec3_t up) {
    return mat4_unit();
}

mat4_t perspective(float fov, float aspect, float min, float max) {
    return mat4_unit();
}

mat4_t translate(mat4_t mat, vec3_t delta) {

}

mat4_t rotate(mat4_t mat, float angle, vec3_t around) {

}

mat4_t scale(mat4_t mat, vec3_t fac) {

}

mat4_t skew(mat4_t mat, vec3_t fac) {

}
