#include "render.h"
#include "wallHitDto.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

static SDL_Texture *texture = NULL;

void drawScreen(RenderContext *renderContext, WallHitDTO *hits) {
  for (int x = 0; x < renderContext->width; x++) {
    drawWall(renderContext, x, hits[x]);
  }
}

void drawWall(RenderContext *renderContext, int x, WallHitDTO hit) {
  const int SCREEN_HEIGHT = renderContext->height;

  int wallHeight = (int)((64 * SCREEN_HEIGHT) / hit.distance);
  int wallTop = (SCREEN_HEIGHT / 2 - wallHeight / 2);
  int wallBottom = wallTop + wallHeight;

  float texW, texH;
  SDL_GetTextureSize(renderContext->wallTexture, &texW, &texH);

  int texX = (int)(hit.textureX * texW);
  if (texX < 0)
    texX = 0;
  if (texX >= texW)
    texX = texW - 1;

  SDL_FRect src = {texX, 0, 1, texH};
  SDL_FRect dst = {x, wallTop, 1, wallHeight};

  SDL_RenderTexture(renderContext->renderer, renderContext->wallTexture, &src,
                    &dst);
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
