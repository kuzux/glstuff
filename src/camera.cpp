#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <camera.h>

camera_t* make_camera(vec3_t pos, vec3_t lookAt, vec3_t up){
    camera_t* res = (camera_t*)malloc(sizeof(camera_t));
    
    if(!res){
        return NULL;
    }

    res->pos = pos;
    res->lookAt = lookAt;
    res->up = up;

    // set up the view matrix
    res->view = look_at(pos, lookAt, up);

    // set up the projection matrix
    res->proj = perspective(deg_to_rad(FOV_DEGREES), ASPECT, MINDIST, MAXDIST);

    return res;
}

void destroy_camera(camera_t* cam){
    free(cam);
}

void update_camera(camera_t* cam){
    cam->view = look_at(cam->pos, cam->lookAt, cam->up);
}

int camera_bind_shader(camera_t* cam, GLuint shader){
    GLint uniView = glGetUniformLocation(shader, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, (const float*)&(cam->view));

    GLint uniProj = glGetUniformLocation(shader, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, (const float*)&(cam->proj));

    return 0;
}
