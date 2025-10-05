#ifndef GAMESPACE_H
#define GAMESPACE_H

#include "camera.h"
#include "map.h"

typedef struct {
  Camera camera;
  int worldScale;
  Map map;
} GameSpace;

#endif
