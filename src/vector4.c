#include "vector4.h"

vec4 vecAdd(vec4 v1, vec4 v2) {
  vec4 sumVec = { 0, 0, 0, 0 };

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
