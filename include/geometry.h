#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#ifdef __cplusplus
extern "C" {
#endif

#define VEC_LOAD_GL(v) (const float*)&(v)

#ifndef VEC2_DEFINED
#define VEC2_DEFINED
typedef struct {
    union { 
        float x;
        float u;
    };

    union { 
        float y;
        float v;
    };
} vec2_t;
#endif

#ifndef VEC3_DEFINED
#define VEC3_DEFINED
typedef struct {
    union { 
        float x;
        float r;
        float u;
    };

    union { 
        float y;
        float g;
        float v;
    };

    union { 
        float z;
        float b;
        float w;
    };
} vec3_t;
#endif

#ifndef VEC4_DEFINED
#define VEC4_DEFINED
typedef struct {
    union { 
        float x;
        float r;
        float u;
    };

    union { 
        float y;
        float g;
        float v;
    };

    union { 
        float z;
        float b;
        float w;
    };

    union {
        float a;
        float t;
    };
} vec4_t;
#endif

#ifndef MAT2_DEFINED
#define MAT2_DEFINED
typedef struct {
    float e[4];
} mat2_t;
#endif

#ifndef MAT3_DEFINED
#define MAT3_DEFINED
typedef struct {
    float e[9];
} mat3_t;
#endif

#ifndef MAT4_DEFINED
#define MAT4_DEFINED
typedef struct {
    float e[16];
} mat4_t;
#endif

vec2_t make_vec2(float, float);
vec3_t make_vec3(float, float, float);
vec4_t make_vec4(float, float, float, float);

float deg_to_rad(float);
float clamp(float, float, float);

vec2_t vec2_num(float);
vec3_t vec3_num(float);
vec4_t vec4_num(float);

vec2_t vec3_xy(vec3_t);
vec3_t vec4_xyz(vec4_t);

mat2_t mat2_zero();
mat3_t mat3_zero();
mat4_t mat4_zero();

mat2_t mat2_unit();
mat3_t mat3_unit();
mat4_t mat4_unit();

float vec2_length(vec2_t);
float vec3_length(vec3_t);
float vec4_length(vec4_t);

vec2_t vec2_invert(vec2_t);
vec3_t vec3_invert(vec3_t);
vec4_t vec4_invert(vec4_t);

vec2_t vec2_add(vec2_t, vec2_t);
vec3_t vec3_add(vec3_t, vec3_t);
vec4_t vec4_add(vec4_t, vec4_t);

vec2_t vec2_multiply(vec2_t, float);
vec3_t vec3_multiply(vec3_t, float);
vec4_t vec4_multiply(vec4_t, float);

vec2_t vec2_normalize(vec2_t);
vec3_t vec3_normalize(vec3_t);
vec4_t vec4_normalize(vec4_t);

float vec2_dot(vec2_t, vec2_t);
float vec3_dot(vec3_t, vec3_t);
float vec4_dot(vec4_t, vec4_t);

float vec2_cross(vec2_t, vec2_t);
vec3_t vec3_cross(vec3_t, vec3_t);

vec2_t vec2_elementwise_mult(vec2_t, vec2_t);
vec3_t vec3_elementwise_mult(vec3_t, vec3_t);
vec4_t vec4_elementwise_mult(vec4_t, vec4_t);

// basic ops
mat2_t mat2_transpose(mat2_t);
mat3_t mat3_transpose(mat3_t);
mat4_t mat4_transpose(mat4_t);

float mat2_det(mat2_t);
float mat3_det(mat2_t);
float mat4_det(mat2_t);

mat2_t mat2_multiply(mat2_t, mat2_t);
mat3_t mat3_multiply(mat3_t, mat3_t);
mat4_t mat4_multiply(mat4_t, mat4_t);

vec2_t mat2_row(mat2_t, int);
vec2_t mat3_row(mat3_t, int);
vec2_t mat4_row(mat4_t, int);

vec2_t mat2_column(mat2_t, int);
vec2_t mat3_column(mat3_t, int);
vec2_t mat4_column(mat4_t, int);

float mat2_at(mat2_t, int, int);
float mat3_at(mat3_t, int, int);
float mat4_at(mat4_t, int, int);

// projection stuff
mat4_t look_at(vec3_t, vec3_t, vec3_t);
mat4_t perspective(float, float, float, float);
mat4_t ortographic(float, float, float, float, float, float);

// graphical transformations
mat4_t translate(mat4_t, vec3_t);
mat4_t rotate(mat4_t, float, vec3_t);
mat4_t scale(mat4_t, vec3_t);
mat4_t shear(mat4_t, vec3_t);

#ifdef __cplusplus
}
#endif

#endif