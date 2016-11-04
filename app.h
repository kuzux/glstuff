#ifndef _APP_H
#define _APP_H

#include <stdint.h>
#include <SDL2/SDL.h>

int app_start();
int app_clean();

int update(SDL_Event evt, uint64_t ticks);
int draw(SDL_Window* win, SDL_GLContext* ctx);

#endif
