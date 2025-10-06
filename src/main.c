#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

#include "gamespace.h"
#include "input.h"
#include "map.h"
#include "raycast.h"
#include "render.h"
#include "wallHitDto.h"
#include <math.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static RenderContext *ctx = NULL;
static Uint64 last_time = 0;
static GameSpace *game = NULL;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define TARGET_FPS 60
#define FRAME_DELAY_MS (1000 / TARGET_FPS)

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

  SDL_Surface *wallSurface = IMG_Load("../assets/textures/grid.png");
  if (!wallSurface) {
    return SDL_APP_FAILURE;
  }

  // Create texture once and assign it to ctx
  ctx = malloc(sizeof(RenderContext));
  ctx->window = window;
  ctx->renderer = renderer;
  ctx->wallTexture = SDL_CreateTextureFromSurface(renderer, wallSurface);
  SDL_DestroySurface(wallSurface);

  if (!ctx->wallTexture) {
    SDL_Log("Failed to create wall texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  ctx->width = WINDOW_WIDTH;
  ctx->height = WINDOW_HEIGHT;

  game = malloc(sizeof(GameSpace));
  vec4 initialPos = {128, 128, 0, 1};
  Camera cam = {initialPos, 5, M_PI / 2};
  game->camera = cam;
  game->worldScale = 64;
  game->map = generate_map(10, 10);

  ctx->font = TTF_OpenFont("../assets/fonts/HomeVideo-BLG6G.ttf", 15);
  if (!ctx->font) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  last_time = SDL_GetPerformanceCounter();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 freq = SDL_GetPerformanceFrequency();

  static Uint64 last_time = 0;
  if (last_time == 0)
    last_time = now;

  float deltaTime = (float)(now - last_time) / freq;

  // Clamp deltaTime
  if (deltaTime > 0.1f)
    deltaTime = 0.1f;
  if (deltaTime < 0.001f)
    deltaTime = 0.001f;

  last_time = now;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  handleInput(game, deltaTime);

  WallHitDTO *hits = raycastLoop(WINDOW_WIDTH, game);
  drawScreen(ctx, hits);
  free(hits);

  char *camVecStr = vecToString(game->camera.pos);
  renderText(ctx, camVecStr);
  free(camVecStr);

  SDL_RenderPresent(renderer);

  Uint64 frameTimeMs = (SDL_GetPerformanceCounter() - now) * 1000 / freq;
  if (frameTimeMs < FRAME_DELAY_MS) {
    SDL_Delay(FRAME_DELAY_MS - frameTimeMs);
  }

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  if (ctx->wallTexture)
    SDL_DestroyTexture(ctx->wallTexture);

  if (ctx) {
    if (ctx->font) {
      TTF_CloseFont(ctx->font);
    }
    free(ctx);

    free_map(&game->map);
    free(game);
    TTF_Quit();
  }
}
