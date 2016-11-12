#include <stdio.h>
#include <geometry.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
    printf("test\n");
    
    #define FOV_DEGREES 90.0f
    #define MINDIST 1.0f
    #define MAXDIST 10.0f
    #define ASPECT 800.0f / 600.0f

    // set up the view matrix
    mat4_t view = look_at(
        make_vec3(2.2f, 2.2f, 2.2f),
        make_vec3(0.0f, 0.0f, 0.0f), 
        make_vec3(0.0f, 0.0f, 1.0f));

    // set up the projection matrix
    mat4_t proj = perspective(deg_to_rad(FOV_DEGREES), ASPECT, MINDIST, MAXDIST);
    
    glm::mat4 glmview = glm::lookAt(
        glm::vec3(2.2f, 2.2f, 2.2f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)); 

    glm::mat4 glmproj = glm::perspective(deg_to_rad(FOV_DEGREES), ASPECT, MINDIST, MAXDIST);

    mat4_t mul = mat4_multiply(proj,view);

    const float* res = VEC_LOAD_GL(mul);
    const float* res2 = glm::value_ptr(glmproj * glmview);

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%f ", res[4*i+j]);
        }
        printf("\n");
    }

    printf("\n");

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%f ", res2[4*i+j]);
        }
        printf("\n");
    }

    return 0;
}
