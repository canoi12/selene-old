#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "selene.h"
#include "quad.h"

typedef struct image_s {
  GLuint _vao, _vbo, _ebo;
  GLuint _tex;
  int _width;
  int _height;
} Image;

Image * selene_create_image(const char * path);

int selene_get_image_width(Image * image);

int selene_get_image_height(Image * image);

void selene_draw_image(Image * image, Quad * quad, int x, int y);

void selene_draw_image_ex(Image * image, Quad * quad, int x, int y, float sx, float sy, float angle, float cx, float cy);

#endif // _IMAGE_H_
