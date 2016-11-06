#ifndef _APP_H
#define _APP_H

#include <stdint.h>
#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

    int app_start();
    int app_clean();

    int update(SDL_Event evt, uint64_t ticks);
    int draw(SDL_Window* win, SDL_GLContext* ctx);
    
#ifdef __cplusplus
}
#endif

#endif
