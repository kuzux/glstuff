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

    const float* view2 = glm::value_ptr(glm::lookAt(
        glm::vec3(2.2f, 2.2f, 2.2f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)));

    const float* proj2 = glm::value_ptr(glm::perspective(deg_to_rad(FOV_DEGREES), ASPECT, MINDIST, MAXDIST));

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%f ", view.e[4*i+j]);
        }
        printf("\n");
    }

    printf("\n");

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%f ", view2[4*i+j]);
        }
        printf("\n");
    }

    printf("\n");

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%f ", proj.e[4*i+j]);
        }
        printf("\n");
    }

    printf("\n");

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%f ", proj2[4*i+j]);
        }
        printf("\n");
    }
    return 0;
}
