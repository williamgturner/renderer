#ifndef RENDER_H
#define RENDER_H

#include "wallHitDto.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  SDL_Texture *wallTexture;
  int width;
  int height;
} RenderContext;

/**
 * Draws a vertical line of pixels at column x of height *height*
 * @param renderContext
 * @param x column to draw wall
 * @param height height of wall
 */
void drawWall(RenderContext *renderContext, int x, WallHitDTO hit);

void drawScreen(RenderContext *renderContext, WallHitDTO *hits);

void renderText(RenderContext *renderContext, const char *message);

#endif
