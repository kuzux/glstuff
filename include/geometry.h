#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#ifdef __cplusplus
extern "C" {
#endif

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

vec2_t make_vec2(float, float);
vec3_t make_vec3(float, float, float);
vec4_t make_vec4(float, float, float, float);

#ifdef __cplusplus
}
#endif

#endif