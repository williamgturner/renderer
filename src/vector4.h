#ifndef VECTOR4_H
#define VECTOR4_H

typedef struct {
  int x, y;
  float dx, dy;
} vec4;

vec4 vecRotate(vec4 v1, float angle);

/* Add two 4-vectors and return the product
 */
vec4 vecAdd(vec4 v1, vec4 v2);

/* Add two 4-vectors and modify in vecAddInPlace
 * @param v1 4-vector to modify
 * @param v2 4-vector to Add
 */
void vecAddInPlace(vec4 *v1, vec4 v2);

float distance(vec4 v0, vec4 v1);

void vecPrint(vec4 v0);

char *vecToString(vec4 v0);

#endif
