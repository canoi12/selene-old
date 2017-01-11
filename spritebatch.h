#ifndef _SPRITEBATCH_H_
#define _SPRITEBATCH_H_

#include "selene.h"

typedef struct image Image;

typedef struct {
  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
  Image * _image;
  int _maxSprites;
  int _currentSprites;
} SpriteBatch;

SpriteBatch * selene_create_sprite_batch(Image * image, int maxSprites);

void selene_sprite_batch_add(SpriteBatch * batch, Quad * quad, int x, int y);

void selene_sprite_batch_draw(SpriteBatch * batch);

#endif // _SPRITEBATCH_H_
