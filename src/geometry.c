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
vec2_t vec3_xy(vec3_t v) {
    return make_vec2(v.x, v.y);
}

vec3_t vec4_xyz(vec4_t v) {
    return make_vec3(v.x, v.y, v.z);
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
    return sqrt(v.x*v.x+v.y*v.y);
}

float vec3_length(vec3_t v) {
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

float vec4_length(vec4_t v) {
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z+v.t*v.t);
}

vec2_t vec2_invert(vec2_t v) {
    return make_vec2(-1.0f*v.x, -1.0f*v.y);
}

vec3_t vec3_invert(vec3_t v) {
    return make_vec3(-1.0f*v.x, -1.0f*v.y, -1.0f*v.z);
}

vec4_t vec4_invert(vec4_t v) {
    return make_vec4(-1.0f*v.x, -1.0f*v.y, -1.0f*v.z, -1.0f*v.t);
}

vec2_t vec2_add(vec2_t a, vec2_t b) {
    return make_vec2(a.x+b.x, a.y+b.y);
}

vec3_t vec3_add(vec3_t a, vec3_t b) {
    return make_vec3(a.x+b.x, a.y+b.y, a.z+b.z);
}

vec4_t vec4_add(vec4_t a, vec4_t b) {
    return make_vec4(a.x+b.x, a.y+b.y, a.z+b.z, a.t+b.t);
}

vec2_t vec2_multiply(vec2_t a, float c) {
    return make_vec2(c*a.x, c*a.y);
}

vec3_t vec3_multiply(vec3_t a, float c) {
    return make_vec3(c*a.x, c*a.y, c*a.z);
}

vec4_t vec4_multiply(vec4_t a, float c) {
    return make_vec4(c*a.x, c*a.y, c*a.z, c*a.t);
}

vec2_t vec2_normalize(vec2_t v) {
    return vec2_multiply(v, 1.0f/vec2_length(v));
}

vec3_t vec3_normalize(vec3_t v) {
    return vec3_multiply(v, 1.0f/vec3_length(v));
}

vec4_t vec4_normalize(vec4_t v) {
    return vec4_multiply(v, 1.0f/vec4_length(v));
}

float vec2_dot(vec2_t a, vec2_t b) {
    return a.x*b.x + a.y*b.y;
}

float vec3_dot(vec3_t a, vec3_t b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

float vec4_dot(vec4_t a, vec4_t b) {
    return a.x*b.x + a.y*b.y + a.z*b.z + a.t*b.t;
}

float vec2_cross(vec2_t a, vec2_t b) {
    return a.x*b.y - a.y*b.x; 
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
    float xc = a.y * b.z - b.y * a.z;
    float yc = a.x * b.z - b.x * a.z;
    float zc = a.x * b.y - b.x * a.y;

    return make_vec3(xc, yc, zc); 
}

mat2_t mat2_transpose(mat2_t m) {

}

mat3_t mat3_transpose(mat3_t m) {

}

mat4_t mat4_transpose(mat4_t m) {

}

float mat2_det(mat2_t m) {

}

float mat3_det(mat2_t m) {

}

float mat4_det(mat2_t m) {

}

mat2_t mat2_multiply(mat2_t m, mat2_t n) { 

}

mat3_t mat3_multiply(mat3_t m, mat3_t n) {

}

mat4_t mat4_multiply(mat4_t m, mat4_t n) {

}

mat4_t look_at(vec3_t pos, vec3_t look, vec3_t up) {
    vec3_t n = vec3_normalize(vec3_add(pos, vec3_invert(look)));
    vec3_t u = vec3_normalize(vec3_cross(up, n));
    vec3_t v = vec3_cross(n, u);

    mat4_t res;

    res.e[0] = u.x;
    res.e[1] = v.x;
    res.e[2] = n.x;
    res.e[3] = 0.0f;

    res.e[4] = u.y;
    res.e[5] = v.y;
    res.e[6] = n.y;
    res.e[7] = 0.0f;

    res.e[8] = u.z;
    res.e[9] = v.z;
    res.e[10] = n.z;
    res.e[11] = 0.0f;

    res.e[12] = vec3_dot(vec3_invert(u), pos);
    res.e[13] = vec3_dot(vec3_invert(v), pos);
    res.e[14] = vec3_dot(vec3_invert(n), pos);
    res.e[15] = 1.0f;

    return res;
}

mat4_t perspective(float fov, float aspect, float min, float max) {
    return mat4_unit();
}

mat4_t ortographic(vec3_t origin, vec3_t size) {
    return mat4_unit();
}

mat4_t translate(mat4_t mat, vec3_t delta) {
    return mat4_unit();
}

mat4_t rotate(mat4_t mat, float angle, vec3_t around) {
    return mat4_unit();
}

mat4_t scale(mat4_t mat, vec3_t fac) {
    return mat4_unit();
}

mat4_t skew(mat4_t mat, vec3_t fac) {
    return mat4_unit();
}
