#include "raycast.h"
#include "camera.h"
#include "map.h"
#include "vector4.h"
#include <math.h>
#include <stdio.h>

float *raycastLoop(int numRays, GameSpace *game) {
  float *rayDistances = malloc(numRays * sizeof(float));
  vec4 rayVec;
  vec4 ray = vecRotate(game->camera.pos, (game->camera.fov / 2) * -1);
  float rayDelta = (game->camera.fov) / numRays;

  for (int x = 0; x < numRays; x++) {
    float distX = 0.0f;
    float distY = 0.0f;

    float angleFromCenter = ((float)x / numRays - 0.5f) * game->camera.fov;

    rayVec = vecRotate(ray, rayDelta * x);
    distY = marchY(rayVec, &game->map, game->worldScale);
    distX = marchX(rayVec, &game->map, game->worldScale);

    float dist = (distY < distX) ? distY : distX;

    rayDistances[x] = dist * cosf(angleFromCenter);
  }

  return rayDistances;
}
/*
 * Marches 4-vector vertically until a wall collision is detected
 * @param 4-vector
 * @param integer array representing game-space
 * @return distance to wall collision
 */
float marchY(vec4 ray, Map *map, int worldScale) {
  if (fabs(ray.dy) < 0.0001f) {
    return INFINITY;
  }

  int stepY;
  float rayY;

  if (ray.dy < 0) {
    stepY = -1;
    rayY = floor(ray.y / worldScale) * worldScale;
  } else {
    stepY = 1;
    rayY = ceil(ray.y / worldScale) * worldScale;
  }

  float slope = ray.dx / ray.dy;
  vec4 newVec = ray;

  while (1) {
    float deltaY = rayY - newVec.y;

    newVec.y = rayY;
    newVec.x = ray.x + (slope * deltaY);

    int intRayX = (int)(newVec.x / worldScale);
    int intRayY = (int)(newVec.y / worldScale);

    // FIX: Cast to float to avoid warning
    if (stepY < 0 && fabs(newVec.y - (float)(intRayY * worldScale)) < 0.001f) {
      intRayY -= 1;
    }

    if (intRayX < 0 || intRayX >= map->width || intRayY < 0 ||
        intRayY >= map->height) {
      return INFINITY;
    }

    if (map->tiles[intRayY][intRayX] == 1) {
      return distance(ray, newVec);
    }

    rayY += stepY * worldScale;
  }
}

float marchX(vec4 ray, Map *map, int worldScale) {
  if (fabs(ray.dx) < 0.0001f) {
    return INFINITY;
  }

  int stepX;
  float rayX;

  if (ray.dx < 0) {
    stepX = -1;
    rayX = floor(ray.x / worldScale) * worldScale;
  } else {
    stepX = 1;
    rayX = ceil(ray.x / worldScale) * worldScale;
  }

  float slope = ray.dy / ray.dx;
  vec4 newVec = ray;

  while (1) {
    float deltaX = rayX - newVec.x;

    newVec.x = rayX;
    newVec.y = ray.y + (slope * deltaX);

    int intRayX = (int)(newVec.x / worldScale);
    int intRayY = (int)(newVec.y / worldScale);

    // FIX: Cast to float to avoid warning
    if (stepX < 0 && fabs(newVec.x - (float)(intRayX * worldScale)) < 0.001f) {
      intRayX -= 1;
    }

    if (intRayX < 0 || intRayX >= map->width || intRayY < 0 ||
        intRayY >= map->height) {
      return INFINITY;
    }

    if (map->tiles[intRayY][intRayX] == 1) {
      return distance(ray, newVec);
    }

    rayX += stepX * worldScale;
  }
}