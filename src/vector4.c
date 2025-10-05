#include "vector4.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

vec4 vecRotate(vec4 v0, float angle) {
  vec4 vecResult = {0, 0, 0, 0};
  float dx0 = v0.dx;
  float dy0 = v0.dy;

  vecResult.x = v0.x;
  vecResult.y = v0.y;

  vecResult.dx = dx0 * cosf(angle) - dy0 * sinf(angle);
  vecResult.dy = dx0 * sinf(angle) + dy0 * cosf(angle);

  return vecResult;
}

vec4 vecAdd(vec4 v1, vec4 v2) {
  vec4 sumVec = {0, 0, 0, 0};

  sumVec.x = v1.x + v2.x;
  sumVec.y = v1.y + v2.y;
  sumVec.dx = v1.dx + v2.dx;
  sumVec.dy = v1.dy + v2.dy;

  return sumVec;
}

void vecAddInPlace(vec4 *v1, vec4 v2) {
  v1->x += v2.x;
  v1->y += v2.y;
  v1->dx += v2.dx;
  v1->dy += v2.dy;
}

float distance(vec4 v0, vec4 v1) {
  float dx = v1.x - v0.x;
  float dy = v1.y - v0.y;
  return (float)sqrt(dx * dx + dy * dy);
}

void vecPrint(vec4 v0) {
  printf("Vec4(x=%.2d, y=%.2d, dx=%.2f, dy=%.2f)\n", v0.x, v0.y, v0.dx, v0.dy);
}

// Returns a dynamically allocated string representing the vec4
char *vecToString(vec4 v0) {
  char *buffer = malloc(100);
  if (!buffer)
    return NULL;

  snprintf(buffer, 100, "Vec4(x=%.2d, y=%.2d, dx=%.2f, dy=%.2f)", v0.x, v0.y,
           v0.dx, v0.dy);

  return buffer;
}
