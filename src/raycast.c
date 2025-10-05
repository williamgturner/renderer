#include "raycast.h"
#include "camera.h"
#include "map.h"
#include "vector4.h"
#include "wallHitDto.h"
#include <float.h>
#include <math.h>
#include <stdio.h>

// Main raycasting loop
WallHitDTO *raycastLoop(int numRays, GameSpace *game) {
  WallHitDTO *hits = malloc(numRays * sizeof(WallHitDTO));
  if (!hits)
    return NULL;

  vec4 baseDir = game->camera.pos;

  for (int x = 0; x < numRays; x++) {
    float angleFromCenter = ((float)x / numRays - 0.5f) * game->camera.fov;
    vec4 rayVec = vecRotate(baseDir, angleFromCenter);

    WallHitDTO hitY = marchY(rayVec, &game->map, game->worldScale);
    WallHitDTO hitX = marchX(rayVec, &game->map, game->worldScale);

    WallHitDTO selected = (hitY.distance < hitX.distance) ? hitY : hitX;

    selected.distance *= cosf(angleFromCenter);

    hits[x] = selected;
  }

  return hits;
}

// Vertical march
WallHitDTO marchY(vec4 ray, Map *map, int worldScale) {
  WallHitDTO result = {.distance = FLT_MAX, .wallType = 0};
  if (fabs(ray.dy) < 0.0001f)
    return result;

  int stepY;
  float rayY;
  int currentTileY = (int)(ray.y / worldScale);

  if (ray.dy > 0) {
    stepY = 1;
    rayY = (currentTileY + 1) * worldScale;
  } else {
    stepY = -1;
    rayY = currentTileY * worldScale;
  }

  float slope = ray.dx / ray.dy;

  while (1) {
    float deltaY = rayY - ray.y;
    float newX = ray.x + slope * deltaY;

    int intX = (int)(newX / worldScale);
    int intY = (int)(rayY / worldScale);
    if (stepY < 0)
      intY -= 1;

    if (intX < 0 || intX >= map->width || intY < 0 || intY >= map->height)
      return result;

    int wallType = map->tiles[intY][intX];
    if (wallType > 0) {
      vec4 hitPoint = {newX, rayY, 0, 0};
      result.distance = distance(ray, hitPoint);
      result.wallType = wallType;
      return result;
    }

    rayY += stepY * worldScale;
  }
}

// Horizontal march
WallHitDTO marchX(vec4 ray, Map *map, int worldScale) {
  WallHitDTO result = {.distance = FLT_MAX, .wallType = 0};
  if (fabs(ray.dx) < 0.0001f)
    return result;

  int stepX;
  float rayX;
  int currentTileX = (int)(ray.x / worldScale);

  if (ray.dx > 0) {
    stepX = 1;
    rayX = (currentTileX + 1) * worldScale;
  } else {
    stepX = -1;
    rayX = currentTileX * worldScale;
  }

  float slope = ray.dy / ray.dx;

  while (1) {
    float deltaX = rayX - ray.x;
    float newY = ray.y + slope * deltaX;

    int intX = (int)(rayX / worldScale);
    int intY = (int)(newY / worldScale);
    if (stepX < 0)
      intX -= 1;

    if (intX < 0 || intX >= map->width || intY < 0 || intY >= map->height)
      return result;

    int wallType = map->tiles[intY][intX];
    if (wallType > 0) {
      vec4 hitPoint = {rayX, newY, 0, 0};
      result.distance = distance(ray, hitPoint);
      result.wallType = wallType;
      return result;
    }

    rayX += stepX * worldScale;
  }
}
