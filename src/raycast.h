#ifndef RAYCAST_H
#define RAYCAST_H

#include "gamespace.h"
#include "map.h"
#include "vector4.h"

float *raycastLoop(int numRays, GameSpace *world);

float marchY(vec4 p0, Map *map, int worldScale);
float marchX(vec4 p0, Map *map, int worldScale);

int detectWall(vec4 v, Map *map);

#endif
