#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
} RenderContext;

void drawWall(RenderContext *renderContext, int x, int height);

#endif
