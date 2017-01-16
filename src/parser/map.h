#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct map Map;

typedef struct map {
  char* key;
  void* value;
  Map* left;
  Map* right;
} Map;

Map * create_map(const char* key, void* value, int size);

void map_add_value(Map* map, const char* key, void* value, int size);

void* map_get_value(Map* map, const char* key);

#endif // _MAP_H_
