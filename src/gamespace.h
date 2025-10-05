#ifndef GAMESPACE_H
#define GAMESPACE_H

#include "player.h"

typedef struct {
  player camera;
  int worldScale;
  int map[100];
} GameSpace;

#endif
