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

#include "app.h"

#include "camera.h"
#include "object.h"

object_t* obj;
camera_t* cam;

int app_start(){
    obj = new_object();
    cam = new_camera(
        glm::vec3(1.2f, 1.2f, 1.2f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    if(!obj) {
        return 1;
    }

    if(!cam) {
        return 1;
    }

    if(compile_shaders(obj)) {
        return 1;
    }
    
    if(link_shaders(obj)) {
        return 1;
    }

    if(load_texture(obj)) { 
        return 1;
    }

    if(bind_data_to_shaders(obj)) {
        return 1;
    }

    if(camera_bind_shader(cam, obj->shader)) {
        return 1;
    }

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
    glClear(GL_COLOR_BUFFER_BIT);
}

int draw(SDL_Window* win, SDL_GLContext* ctx){
    clear_screen();

    bind_buffers(obj);
    object_draw(obj);

    return 0;
}
