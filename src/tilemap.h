#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include "parser/xmldoc.h"
#include "selene.h"

typedef struct tilemap {
  xmlDoc* doc;
  int* tiles;
  int** map;
} Tilemap;

Tilemap* selene_create_tilemap(const char* path);

void selene_draw_tilemap(Tilemap* tilemap);

#endif // _TILEMAP_H_
