#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "selene.h"
#include "quad.h"

typedef struct image {
  GLuint _vao, _vbo, _ebo;
  GLuint _tex;
  int _width;
  int _height;
  char * _filtermin;
  char * _filtermag;
  char * _wraps;
  char * _wrapt;
} Image;

Image * selene_create_image(const char * path);

void selene_set_image_filter(Image * image, const char * filtermin, const char * filtermag);

void selene_set_image_wrap(Image * image, const char * wraps, const char * wrapt);

int selene_get_image_width(Image * image);

int selene_get_image_height(Image * image);

void selene_draw_image(Image * image, Quad * quad, int x, int y);

void selene_draw_image_ex(Image * image, Quad * quad, int x, int y, float sx, float sy, float angle, float cx, float cy);

void selene_destroy_image(Image* image);

#endif // _IMAGE_H_
