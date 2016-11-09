#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>

#include <SDL2/SDL.h>

#include <app.h>

#include <camera.h>
#include <object.h>
#include <light.h>
#include <objparse.h>
#include <mtlparse.h>

object_t* obj;
camera_t* cam;
light_t* light;

int app_start(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_GEQUAL, 1, 0xFF);
    glStencilMask(0x00);

    obj = make_object();
    cam = make_camera(
        glm::vec3(2.2f, 2.2f, 2.2f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    light = make_light(
        make_vec3(2.0f, 2.0f, 10.0f),
        make_vec3(1.0f, 1.0f, 1.0f), 
        60.0);

    if(!obj) {
        return 1;
    }

    if(!cam) {
        return 1;
    }

    obj_file_t* objfile = make_obj_file("resource/cube.obj");

    if(parse_obj_file(objfile)) {
        return 1;
    }

    mtl_file_t* mtlfile = NULL;

    if(objfile->mtl_file) {
        mtlfile = make_mtl_file(objfile->mtl_file);

        if(parse_mtl_file(mtlfile)) {
            return 1;
        }
    }

    if(init_from_obj_file(obj, objfile, mtlfile)) {
        return 1;
    }

    if(bind_data_to_shaders(obj, light)) {
        return 1;
    }

    if(camera_bind_shader(cam, obj->shader)) {
        return 1;
    }

    delete_obj_file(objfile);

    return 0;
}

int app_clean(){
    return 0;
}

int update(SDL_Event evt, uint64_t ticks){
    object_update(obj, evt, ticks);
    
    return 0;
}

void clear_screen() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int draw(SDL_Window* win, SDL_GLContext* ctx){
    clear_screen();

    bind_buffers(obj);
    object_draw(obj);

    return 0;
}
