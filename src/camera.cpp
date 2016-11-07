#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <camera.h>

camera_t* make_camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up){
    camera_t* res = (camera_t*)malloc(sizeof(camera_t));
    
    if(!res){
        return NULL;
    }

    res->pos = pos;
    res->lookAt = lookAt;
    res->up = up;

    // set up the view matrix
    res->view = glm::lookAt(pos, lookAt, up);

    // set up the projection matrix
    res->proj = glm::perspective(glm::radians(FOV_DEGREES), ASPECT, MINDIST, MAXDIST);

    return res;
}

void destroy_camera(camera_t* cam){
    free(cam);
}

void update_camera(camera_t* cam){
    cam->view = glm::lookAt(cam->pos, cam->lookAt, cam->up);
}

int camera_bind_shader(camera_t* cam, GLuint shader){
    GLint uniView = glGetUniformLocation(shader, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(cam->view));

    GLint uniProj = glGetUniformLocation(shader, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(cam->proj));

    return 0;
}
