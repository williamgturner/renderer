#include "render.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Texture *texture = NULL;

void drawScreen(RenderContext *renderContext, float *distances) {
  for (int x = 0; x < renderContext->width; x++) {
    drawWall(renderContext, x, distances[x]);
  }
}

void drawWall(RenderContext *renderContext, int x, float distance) {
  const int SCREEN_HEIGHT = renderContext->height;
  const int SCREEN_WIDTH = renderContext->width;
  int wallHeight = (int)((64 * SCREEN_HEIGHT) / distance); // remove magic num

  int wall_top = (SCREEN_HEIGHT / 2 - wallHeight / 2);
  int wall_bottom = wall_top + wallHeight;

  SDL_SetRenderDrawColor(renderContext->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderLine(renderContext->renderer, x, 0, x, wall_top);
  SDL_RenderLine(renderContext->renderer, x, wall_bottom, x, SCREEN_HEIGHT);

  SDL_SetRenderDrawColor(renderContext->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderLine(renderContext->renderer, x, wall_top, x, wall_bottom);
}

void renderText(RenderContext *renderContext, const char *message) {
  SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};
  SDL_Surface *text =
      TTF_RenderText_Blended(renderContext->font, message, 0, color);

  if (!text) {
    SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    return;
  }

  texture = SDL_CreateTextureFromSurface(renderContext->renderer, text);
  SDL_DestroySurface(text);

  if (!texture) {
    SDL_Log("Couldn't create texture: %s\n", SDL_GetError());
    return;
  }

  int w = 0, h = 0;
  SDL_FRect dst;
  SDL_GetRenderOutputSize(renderContext->renderer, &w, &h);
  SDL_GetTextureSize(texture, &dst.w, &dst.h);

  dst.x = 10;
  dst.y = h - dst.h - 10;

  SDL_RenderTexture(renderContext->renderer, texture, NULL, &dst);
}
