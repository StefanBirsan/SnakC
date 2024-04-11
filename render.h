#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>

void render_snake(SDL_Renderer *renderer, int x, int y);
void render_grid(SDL_Renderer *renderer, int x, int y);
void render_apple(SDL_Renderer *renderer, int x, int y);
void render_score(SDL_Renderer *renderer, int x, int y, int size);
void render_high_score(SDL_Renderer *renderer, int x, int y, int size);

#endif //RENDER_H