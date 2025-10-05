#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int width;
    int height;
} RenderContext;

void drawWall(RenderContext *renderContext, int x, int height);

void renderText(RenderContext *renderContext, const char *messagn);

#endif
