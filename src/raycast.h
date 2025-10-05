#ifndef RAYCAST_H
#define RAYCAST_H

#include "gamespace.h"
#include "vector4.h"

void raycastLoop(int numRays, GameSpace *world);

vec4 marchRay(vec4 p0, int map[]);

int detectWall(vec4 v, int map[]);

#endif
