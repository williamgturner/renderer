#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

#include "raycast.h"
#include "render.h"
#include "gamespace.h"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static RenderContext *ctx = NULL;
static Uint64 last_time = 0;
static GameSpace *game = NULL;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    int i;

    SDL_SetAppMetadata("2.5D Raycast Renderer", "0.1", "com.example.williamturner");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/points", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
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
    vec4 initialPos = { 128, 128, 0, 0 };
    player camera = {initialPos, 1};
    game->camera = camera;
   game->worldScale = 64;
  int map[100];  // 10x10 flattened into 1D

for (int y = 0; y < 10; y++) {
    for (int x = 0; x < 10; x++) {
        if (y == 0 || y == 9 || x == 0 || x == 9) {
            map[y * 10 + x] = 1;  // wall
        } else {
            map[y * 10 + x] = 0;
        }
    }
}

// copy into your GameSpace struct
memcpy(game->map, map, sizeof(map));


  /* Open the font */
    ctx->font = TTF_OpenFont("../assets/fonts/HomeVideo-BLG6G.ttf", 30);
    if (!ctx->font) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    last_time = SDL_GetTicks();
    
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    const Uint64 now = SDL_GetTicks();
    const float elapsed = ((float) (now - last_time)) / 1000.0f;  /* seconds since last iteration */
    int i;
    last_time = now;


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    raycastLoop(game);
    drawWall(ctx, 400, 300);
    renderText(ctx, "Test...");

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
if (ctx) {
    if (ctx->font) {
        TTF_CloseFont(ctx->font);
    }
    free(ctx);
}
  free(game);
 TTF_Quit();
}

