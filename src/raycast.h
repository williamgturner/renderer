#ifndef RAYCAST_H
#define RAYCAST_H

#include "vector4.h"

vec4 marchRay(vec4 p0, int map[]);

bool detectWall(vec4 v, int map[]);


#endif
