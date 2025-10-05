#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

#include "gamespace.h"
#include "input.h"
#include "map.h"
#include "raycast.h"
#include "render.h"
#include "wallHitDto.h"
#include <math.h>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static RenderContext *ctx = NULL;
static Uint64 last_time = 0;
static GameSpace *game = NULL;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  int i;

  SDL_SetAppMetadata("2.5D Raycast Renderer", "0.1",
                     "com.example.williamturner");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("raycaster", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                   &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!TTF_Init()) {
    SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  ctx = malloc(sizeof(RenderContext));
  ctx->window = window;
  ctx->renderer = renderer;
  ctx->width = WINDOW_WIDTH;
  ctx->height = WINDOW_HEIGHT;

  game = malloc(sizeof(GameSpace));
  vec4 initialPos = {128, 128, 0, 1};
  Camera cam = {initialPos, 5, M_PI / 2};
  game->camera = cam;
  game->worldScale = 64;
  game->map = generate_map(10, 10);

  /* Open the font */
  ctx->font = TTF_OpenFont("../assets/fonts/HomeVideo-BLG6G.ttf", 15);
  if (!ctx->font) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  last_time = SDL_GetTicks();

  return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }
  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
  const Uint64 now = SDL_GetTicks();
  const float elapsed =
      ((float)(now - last_time)) / 1000.0f; /* seconds since last iteration */
  int i;
  last_time = now;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0,
                         SDL_ALPHA_OPAQUE); /* black, full alpha */
  SDL_RenderClear(renderer);
  handleInput(game, elapsed);

  WallHitDTO *hits = raycastLoop(WINDOW_WIDTH, game);

  drawScreen(ctx, hits);

  free(hits);

  char *camVecStr = vecToString(game->camera.pos);
  renderText(ctx, camVecStr);
  free(camVecStr);

  SDL_RenderPresent(renderer);
  return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  if (ctx) {
    if (ctx->font) {
      TTF_CloseFont(ctx->font);
    }
    free(ctx);
  }
  free_map(&game->map);
  free(game);
  TTF_Quit();
}
