#ifndef VECTOR4_H
#define VECTOR4_H

typedef struct {
  int x, y;
  double dx, dy;
} vec4;

/* Add two 4-vectors and return the product
*/
vec4 vecAdd(vec4 v1, vec4 v2);

/* Add two 4-vectors and modify in vecAddInPlace
 * @param v1 4-vector to modify
 * @param v2 4-vector to Add
*/
void vecAddInPlace(vec4 *v1, vec4 v2);

#endif
