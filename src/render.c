#include "render.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

void drawWall(RenderContext *renderContext, int x, int height) {
  const int SCREEN_HEIGHT = renderContext->height;
  const int SCREEN_WIDTH = renderContext->width;
  int wall_top = (SCREEN_HEIGHT  / 2 - height / 2);
  int wall_bottom = wall_top + height;
  SDL_RenderLine(renderContext->renderer, x, wall_top, x, wall_bottom);
}
