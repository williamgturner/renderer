#ifndef RAYCAST_H
#define RAYCAST_H

#include "vector4.h"
#include "gamespace.h"
void raycastLoop(GameSpace *game);

vec4 marchRay(vec4 p0, int map[]);

int detectWall(vec4 v, int map[]);


#endif
