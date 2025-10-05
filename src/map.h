#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

typedef struct {
  int width;
  int height;
  int **tiles;
} Map;

/* Create a map with given width and height. Allocates memory dynamically. */
static inline Map generate_map(int width, int height) {
  Map map;
  map.width = width;
  map.height = height;

  map.tiles = malloc(height * sizeof(int *));
  for (int y = 0; y < height; y++) {
    map.tiles[y] = malloc(width * sizeof(int));
  }

  // fill map: 1 for perimeter, 0 inside
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
        map.tiles[y][x] = 1; // wall
      } else {
        map.tiles[y][x] = 0; // empty
      }
    }
  }

  map.tiles[2][3] = 2;
  map.tiles[4][5] = 3;
  map.tiles[6][7] = 4;
  return map;
}

/* Free the memory used by the map. */
static inline void free_map(Map *map) {
  if (!map || !map->tiles)
    return;

  for (int y = 0; y < map->height; y++) {
    free(map->tiles[y]);
  }
  free(map->tiles);

  map->tiles = NULL;
  map->width = 0;
  map->height = 0;
}

#endif
