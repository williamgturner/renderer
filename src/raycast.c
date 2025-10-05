#include "raycast.h"

/*
 * Increments 4-vector by its magnitude until it intersects with a detectWall
 * @param 4-vector
 * @param integer array representing game-space
*/
vec4 marchRay(vec4 v1, int map[]) {
  while (detectWall(v1, map) < 1) {
    v1->x += v1->dx;
    v1->y += v2->dy;
  }
}
