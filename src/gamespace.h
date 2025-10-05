#ifndef GAMESPACE_H
#define GAMESPACE_H

#include "camera.h"

typedef struct {
  camera camera;
  int worldScale;
  int map[100];
} GameSpace;

#endif
