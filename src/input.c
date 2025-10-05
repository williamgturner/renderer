#include "input.h"
#include "vector4.h"
#include <math.h>
#include <stdbool.h>

static InputConfig config = {200.0f, 2.0f};

InputConfig createInputConfig(float moveSpeed, float rotSpeed) {
  InputConfig cfg = {moveSpeed, rotSpeed};
  return cfg;
}

void handleInput(GameSpace *game, float deltaTime) {
  const bool *keys = SDL_GetKeyboardState(NULL);

  float moveSpeed = config.moveSpeed * deltaTime;
  float rotSpeed = config.rotSpeed * deltaTime;

  // Rotation
  if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
    vec4 rotated = vecRotate(game->camera.pos, rotSpeed);
    game->camera.pos.dx = rotated.dx;
    game->camera.pos.dy = rotated.dy;
  }
  if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
    vec4 rotated = vecRotate(game->camera.pos, -rotSpeed);
    game->camera.pos.dx = rotated.dx;
    game->camera.pos.dy = rotated.dy;
  }

  // Forward/Backward
  if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
    game->camera.pos.x += game->camera.pos.dx * moveSpeed;
    game->camera.pos.y += game->camera.pos.dy * moveSpeed;
  }
  if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
    game->camera.pos.x -= game->camera.pos.dx * moveSpeed;
    game->camera.pos.y -= game->camera.pos.dy * moveSpeed;
  }

  // Strafe left/right
  if (keys[SDL_SCANCODE_Q]) {
    game->camera.pos.x += -game->camera.pos.dy * moveSpeed;
    game->camera.pos.y += game->camera.pos.dx * moveSpeed;
  }
  if (keys[SDL_SCANCODE_E]) {
    game->camera.pos.x += game->camera.pos.dy * moveSpeed;
    game->camera.pos.y += -game->camera.pos.dx * moveSpeed;
  }
}