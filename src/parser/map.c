#include "map.h"

Map * create_map(const char* key, void* value, int size) {
  Map* map = malloc(sizeof(*map));
  int ssize = strlen(key);
  map->key = malloc(sizeof(char) * ssize);
  memset(map->key, 0, sizeof(char) * ssize);

  map->value = malloc(size);
  memset(map->value, 0, size);

  strcpy(map->key, (char*)key);
  //memcpy(map->value, value, size);
  (map->value) = value;
  map->left = NULL;
  map->right = NULL;

  return map;
}

void map_add_value(Map* map, const char* key, void* value, int size) {

  if (!strcmp(key, map->key)) {
    printf("Chave %s já existe\n", key);
    return;
  } else if(strcmp(key, map->key) > 0) {
    if (map->right)
      map_add_value(map->right, key, value, size);
    else
      map->right = create_map(key, value, size);
  } else {
    if (map->left)
      map_add_value(map->left, key, value, size);
    else
      map->left = create_map(key, value, size);
  }
}

void* map_get_value(Map* map, const char* key) {

  if (!strcmp(key, map->key)) {
    return map->value;
  }
  else if(strcmp(key, map->key) > 0) {
    if (map->right)
      return map_get_value(map->right, key);
    else {
      printf("Chave não encontrada\n");
      return NULL;
    }
  } else {
    if (map->left)
      return map_get_value(map->left, key);
    else {
      printf("Chave não encontrada\n");
      return NULL;
    }
  }
}
