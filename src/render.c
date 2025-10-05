#include "render.h"
#include "wallHitDto.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Texture *texture = NULL;

void drawScreen(RenderContext *renderContext, WallHitDTO *hits) {
  for (int x = 0; x < renderContext->width; x++) {
    drawWall(renderContext, x, hits[x]);
  }
}

void drawWall(RenderContext *renderContext, int x, WallHitDTO hit) {
  const int SCREEN_HEIGHT = renderContext->height;
  int wallHeight =
      (int)((64 * SCREEN_HEIGHT) / hit.distance); // scale wall height

  int wall_top = (SCREEN_HEIGHT / 2 - wallHeight / 2);
  int wall_bottom = wall_top + wallHeight;

  SDL_SetRenderDrawColor(renderContext->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderLine(renderContext->renderer, x, 0, x, wall_top);
  SDL_RenderLine(renderContext->renderer, x, wall_bottom, x, SCREEN_HEIGHT);

  // Set wall color based on wallType
  switch (hit.wallType) {
  case 1:
    SDL_SetRenderDrawColor(renderContext->renderer, 255, 0, 0,
                           SDL_ALPHA_OPAQUE); // red
    break;
  case 2:
    SDL_SetRenderDrawColor(renderContext->renderer, 0, 255, 0,
                           SDL_ALPHA_OPAQUE); // green
    break;
  case 3:
    SDL_SetRenderDrawColor(renderContext->renderer, 0, 0, 255,
                           SDL_ALPHA_OPAQUE); // blue
    break;
  case 4:
    SDL_SetRenderDrawColor(renderContext->renderer, 255, 255, 0,
                           SDL_ALPHA_OPAQUE); // yellow
    break;
  default:
    SDL_SetRenderDrawColor(renderContext->renderer, 200, 200, 200,
                           SDL_ALPHA_OPAQUE); // gray
    break;
  }

  // Draw the wall slice
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
