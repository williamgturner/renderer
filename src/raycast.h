#ifndef RAYCAST_H
#define RAYCAST_H

#include "gamespace.h"
#include "map.h"
#include "vector4.h"
#include "wallHitDto.h"
#include <stdlib.h>

WallHitDTO *raycastLoop(int numRays, GameSpace *game);
WallHitDTO marchY(vec4 p0, Map *map, int worldScale);
WallHitDTO marchX(vec4 p0, Map *map, int worldScale);

#endif