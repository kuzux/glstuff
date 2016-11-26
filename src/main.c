#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <app.h>

#include <conf.h>

#define FRAME_TIME_MS (1000/FPS)

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
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    if(VSYNC) {
        SDL_GL_SetSwapInterval(1);
    } else {
        SDL_GL_SetSwapInterval(0);
    }

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
    uint64_t ticks = 0;

    if(argc < 2) {
        printf("usage: %s scenefile\n", argv[0]);
        return 1;
    }

    if(app_start(argv[1])) {
        return 1;
    }

    while(running) {
        SDL_Event evt;
        int evt_count = 0;

        int start = SDL_GetTicks();

        while(SDL_PollEvent(&evt)) {
            evt_count++;
            
            if(evt.type == SDL_QUIT) {
                running = 0;
                break;
            }

            if(update(evt, ticks)) {
                running = 0;
                break;
            }
        }

        if(!evt_count) {
            SDL_Event none;
            none.type = 0;

            if(update(none, ticks)) {
                running = 0;
            }
        }

        if(draw(win, ctx)) {
            running = 0;
        }

        int diff = SDL_GetTicks() - start;
        int delay = FRAME_TIME_MS - diff;
        
        if (delay > 0) {
            SDL_Delay(delay);
        }

        SDL_GL_SwapWindow(win);

        ticks++;
    }

    app_clean();

    cleanup();
    return 0;
}
