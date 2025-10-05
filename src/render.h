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

/**
 * Draws a vertical line of pixels at column x of height *height*
 * @param renderContext
 * @param x column to draw wall
 * @param height height of wall
 */
void drawWall(RenderContext *renderContext, int x, float height);

void drawScreen(RenderContext *renderContext, float *distances);

void renderText(RenderContext *renderContext, const char *message);

#endif
