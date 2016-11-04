#ifndef _APP_H
#define _APP_H

#include <SDL2/SDL.h>

int update(SDL_Event evt);
int draw(SDL_Window* win, SDL_GLContext* ctx);

#endif
