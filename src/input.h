#ifndef INPUT_H
#define INPUT_H

#include "gamespace.h"
#include <SDL3/SDL.h>

typedef struct {
  float moveSpeed;
  float rotSpeed;
} InputConfig;

void handleInput(GameSpace *game, float deltaTime);
InputConfig createInputConfig(float moveSpeed, float rotSpeed);

#endif