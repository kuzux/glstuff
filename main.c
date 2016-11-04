#include <stdio.h>
#include <SDL2/SDL.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include "app.h"

#include "conf.h"

SDL_Window* win;
SDL_GLContext* ctx;

int init(){
    if(SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        exit(1);
    }

    win = SDL_CreateWindow(WINDOW_TITLE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(!win) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        
        SDL_Quit();
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetSwapInterval(1);

    ctx = SDL_GL_CreateContext(win);

    if(!win) {
        printf("SDL_GL_CreateContext error: %s\n", SDL_GetError());
        
        SDL_Quit();
        exit(1);
    }

    #ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
    #endif

    return 0;
}

int cleanup(){
    SDL_GL_DeleteContext(ctx);

    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}

int main(int argc, char** argv) {
    init();

    int running = 1;

    while(running) {
        SDL_Event evt;
        while(SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT) {
                running = 0;
            }

            if(update(evt)) {
                running = 0;
            }

            if(draw(win, ctx)) {
                running = 0;
            }
        }
    }

    cleanup();
    return 0;
}
