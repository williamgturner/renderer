#include "raycast.h"
#include "camera.h"
#include "vector4.h"
#include <stdio.h>

void raycastLoop(int numRays, GameSpace *game) {
  vec4 rayVec;
  vec4 ray = vecRotate(game->camera.pos, (game->camera.fov / 2) * -1);
  float rayDelta = (game->camera.fov) / numRays;

  for (int x = 0; x < numRays; x++) {
    rayVec = vecRotate(ray, rayDelta * x);
  }
}
/*
 * Increments 4-vector by its magnitude until it intersects with a wall
 * @param 4-vector
 * @param integer array representing game-space
 */
vec4 marchRay(vec4 v1, int map[]) { return v1; }
