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

float clamp(float v, float min, float max) {
    if(v < min) {
        return min;
    } else if(v > max) {
        return max;
    } else {
        return v;
    }
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
    float yc = a.z * b.x - b.z * a.x;
    float zc = a.x * b.y - b.x * a.y;

    return make_vec3(xc, yc, zc); 
}

vec2_t vec2_elementwise_mult(vec2_t a, vec2_t b) {
    return make_vec2(a.x*b.x, a.y*b.y);
}

vec3_t vec3_elementwise_mult(vec3_t a, vec3_t b) {
    return make_vec3(a.x*b.x, a.y*b.y, a.z*b.z);
}

vec4_t vec4_elementwise_mult(vec4_t a, vec4_t b) {
    return make_vec4(a.x*b.x, a.y*b.y, a.z*b.z, a.t*b.t);
}

mat2_t mat2_transpose(mat2_t m) {
    mat2_t res;

    res.e[0] = m.e[0];
    res.e[1] = m.e[2];

    res.e[2] = m.e[1];
    res.e[3] = m.e[3];

    return res;
}

mat3_t mat3_transpose(mat3_t m) {
    mat3_t res;

    res.e[0] = m.e[0];
    res.e[1] = m.e[3];
    res.e[2] = m.e[6];

    res.e[3] = m.e[1];
    res.e[4] = m.e[4];
    res.e[5] = m.e[7];

    res.e[6] = m.e[2];
    res.e[7] = m.e[5];
    res.e[8] = m.e[8];

    return res;
}

mat4_t mat4_transpose(mat4_t m) {
    mat4_t res;

    res.e[0] = m.e[0];
    res.e[1] = m.e[4];
    res.e[2] = m.e[8];
    res.e[3] = m.e[12];

    res.e[4] = m.e[1];
    res.e[5] = m.e[5];
    res.e[6] = m.e[9];
    res.e[7] = m.e[13];

    res.e[8] = m.e[2];
    res.e[9] = m.e[6];
    res.e[10] = m.e[10];
    res.e[11] = m.e[14];
    
    res.e[12] = m.e[3];
    res.e[13] = m.e[7];
    res.e[14] = m.e[11];
    res.e[15] = m.e[15];

    return res;
}

float mat2_det(mat2_t m) {
    // TODO
    return 0.0f;
}

float mat3_det(mat2_t m) {
    // TODO
    return 0.0f;
}

float mat4_det(mat2_t m) {
    // TODO
    return 0.0f;
}

mat2_t mat2_multiply(mat2_t m, mat2_t n) { 
    mat2_t res;

    res.e[0] = m.e[0]*n.e[0] + m.e[1]*n.e[2];
    res.e[1] = m.e[0]*n.e[1] + m.e[1]*n.e[3];

    res.e[2] = m.e[2]*n.e[0] + m.e[3]*n.e[2];
    res.e[3] = m.e[2]*n.e[1] + m.e[3]*n.e[3];

    return res;
}

mat3_t mat3_multiply(mat3_t m, mat3_t n) {
    mat3_t res;

    res.e[0] = m.e[0]*n.e[0] + m.e[1]*n.e[3] + m.e[2]*n.e[6];
    res.e[1] = m.e[0]*n.e[1] + m.e[1]*n.e[4] + m.e[2]*n.e[7];
    res.e[2] = m.e[0]*n.e[2] + m.e[1]*n.e[5] + m.e[2]*n.e[8];

    res.e[3] = m.e[3]*n.e[0] + m.e[4]*n.e[3] + m.e[5]*n.e[6];
    res.e[4] = m.e[3]*n.e[1] + m.e[4]*n.e[4] + m.e[5]*n.e[7];
    res.e[5] = m.e[3]*n.e[2] + m.e[4]*n.e[5] + m.e[5]*n.e[8];

    res.e[6] = m.e[6]*n.e[0] + m.e[7]*n.e[3] + m.e[8]*n.e[6];
    res.e[7] = m.e[6]*n.e[1] + m.e[7]*n.e[4] + m.e[8]*n.e[7];
    res.e[8] = m.e[6]*n.e[2] + m.e[7]*n.e[5] + m.e[8]*n.e[8];

    return res;
}

mat4_t mat4_multiply(mat4_t m, mat4_t n) {
    mat4_t res;

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        int sum = 0;
        for (int k = 0; k < 4; k++) {
          sum += m.e[4*i+k]*n.e[4*k+j];
        }
 
        res.e[4*i+j] = sum;
      }
    }

    /*res.e[0]  = m.e[0]*n.e[0]  + m.e[1]*n.e[4]  + m.e[2]*n.e[ 8]  + m.e[3]*n.e[12];
    res.e[1]  = m.e[0]*n.e[1]  + m.e[1]*n.e[5]  + m.e[2]*n.e[ 9]  + m.e[3]*n.e[13];
    res.e[2]  = m.e[0]*n.e[2]  + m.e[1]*n.e[6]  + m.e[2]*n.e[10]  + m.e[3]*n.e[14];
    res.e[3]  = m.e[0]*n.e[3]  + m.e[1]*n.e[7]  + m.e[2]*n.e[11]  + m.e[3]*n.e[15];

    res.e[4]  = m.e[4]*n.e[0]  + m.e[5]*n.e[4]  + m.e[6]*n.e[ 8]  + m.e[7]*n.e[12];
    res.e[5]  = m.e[4]*n.e[1]  + m.e[5]*n.e[5]  + m.e[6]*n.e[ 9]  + m.e[7]*n.e[13];
    res.e[6]  = m.e[4]*n.e[2]  + m.e[5]*n.e[6]  + m.e[6]*n.e[10]  + m.e[7]*n.e[14];
    res.e[7]  = m.e[4]*n.e[3]  + m.e[5]*n.e[7]  + m.e[6]*n.e[11]  + m.e[7]*n.e[15];

    res.e[8]  = m.e[8]*n.e[0]  + m.e[9]*n.e[4]  + m.e[10]*n.e[ 8] + m.e[11]*n.e[12];
    res.e[9]  = m.e[8]*n.e[1]  + m.e[9]*n.e[5]  + m.e[10]*n.e[ 9] + m.e[11]*n.e[13];
    res.e[10] = m.e[8]*n.e[2]  + m.e[9]*n.e[6]  + m.e[10]*n.e[10] + m.e[11]*n.e[14];
    res.e[11] = m.e[8]*n.e[3]  + m.e[9]*n.e[7]  + m.e[10]*n.e[11] + m.e[11]*n.e[15];

    res.e[12] = m.e[12]*n.e[0] + m.e[13]*n.e[4] + m.e[14]*n.e[ 8] + m.e[15]*n.e[12];
    res.e[13] = m.e[12]*n.e[1] + m.e[13]*n.e[5] + m.e[14]*n.e[ 9] + m.e[15]*n.e[13];
    res.e[14] = m.e[12]*n.e[2] + m.e[13]*n.e[6] + m.e[14]*n.e[10] + m.e[15]*n.e[14];
    res.e[15] = m.e[12]*n.e[3] + m.e[13]*n.e[7] + m.e[14]*n.e[11] + m.e[15]*n.e[15];*/

    return res;
}

vec2_t mat2_row(mat2_t m, int i) {
    return make_vec2(m.e[2*i],m.e[2*i+1]);
}

vec3_t mat3_row(mat3_t m, int i) {
    return make_vec3(m.e[3*i],m.e[3*i+1],m.e[3*i+2]);
}

vec4_t mat4_row(mat4_t m, int i) {
    return make_vec4(m.e[4*i],m.e[4*i+1],m.e[4*i+2],m.e[4*i+3]);
}

vec2_t mat2_column(mat2_t m, int i) {
    return make_vec2(m.e[2*0+i],m.e[2*1+i]);
}

vec3_t mat3_column(mat3_t m, int i) {
    return make_vec3(m.e[3*0+i],m.e[3*1+i],m.e[3*2+i]);
}

vec4_t mat4_column(mat4_t m, int i) {
    return make_vec4(m.e[4*0+i],m.e[4*1+i],m.e[4*2+i],m.e[4*3+i]);
}

float mat2_at(mat2_t m, int i, int j) {
    return m.e[2*i+j];
}

float mat3_at(mat3_t m, int i, int j) {
    return m.e[3*i+j];
}

float mat4_at(mat4_t m, int i, int j) {
    return m.e[4*i+j];
}

mat4_t look_at(vec3_t eye, vec3_t center, vec3_t up) {
    vec3_t f = vec3_normalize(vec3_add(center, vec3_invert(eye)));
    vec3_t s = vec3_normalize(vec3_cross(f, up));
    vec3_t u = vec3_cross(s, f);

    mat4_t res;

    res.e[0] =  s.x;
    res.e[1] =  u.x;
    res.e[2] = -f.x;
    res.e[3] = 0.0f;

    res.e[4] =  s.y;
    res.e[5] =  u.y;
    res.e[6] = -f.y;
    res.e[7] = 0.0f;

    res.e[8]  =  s.z;
    res.e[9]  =  u.z;
    res.e[10] = -f.z;
    res.e[11] = 0.0f;

    res.e[12] = -vec3_dot(s, eye);
    res.e[13] = -vec3_dot(u, eye);
    res.e[14] =  vec3_dot(f, eye);
    res.e[15] = 1.0f;

    return res;
}

mat4_t perspective(float fov, float aspect, float near, float far) {
    mat4_t res = mat4_zero();

    float f = tan(fov/2.0f);

    res.e[0]  =   1 / (aspect * f);
    res.e[5]  =   1 / f;
    res.e[10] = - (far + near) / (far - near);
    res.e[11] = - 1.0f;
    res.e[14] = - (2.0f * far * near) / (far - near);

    return res;
}

mat4_t ortographic(float l, float r, float b, float t, float n, float f) {
    mat4_t res = mat4_zero();

    res.e[0]  =  2.0f/(r-l);
    res.e[5]  =  2.0f/(t-b);
    res.e[10] = -2.0f/(f-n);
    res.e[15] =  1.0f;

    res.e[3]  = -(r+l)/(r-l);
    res.e[7]  = -(t+b)/(t-n);
    res.e[11] = -(f+n)/(f-n);

    return res;
}

mat4_t translate(mat4_t mat, vec3_t delta) {
    mat4_t res = mat4_unit();
    
    res.e[3]  = delta.x;
    res.e[7]  = delta.y;
    res.e[11] = delta.z;

    return mat4_multiply(res, mat);
}

mat4_t rotate(mat4_t mat, float angle, vec3_t around) {
    // use the formula at the end of this page
    // http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/
    // replacing a,b,c = 0
    mat4_t res = mat4_unit();

    /*vec3_t n = vec3_normalize(around);

    float u = n.u;
    float v = n.v;
    float w = n.w;

    float s   = sin(angle);
    float c   = cos(angle);*/



    return mat4_multiply(res, mat);
}

mat4_t scale(mat4_t mat, vec3_t fac) {
    mat4_t res = mat4_unit();

    res.e[0]  = fac.x;
    res.e[5]  = fac.y;
    res.e[10] = fac.z;

    return mat4_multiply(res, mat);
}

mat4_t shear(mat4_t mat, vec3_t fac) {
    mat4_t res = mat4_unit();

    return mat4_multiply(res, mat);
}
