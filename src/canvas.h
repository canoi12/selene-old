#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "selene.h"

typedef struct canvas {
  GLuint _vao;
  GLuint _vbo;
  GLuint _fbo;
  GLuint _rbo;
  GLuint _texture;
  int _width;
  int _height;
} Canvas;

Canvas * selene_create_canvas(int width, int height);

GLuint selene_gen_attach_texture(GLboolean depth, GLboolean stencil, int width, int height);

void selene_set_canvas(Canvas * canvas);

void selene_draw_canvas(Canvas * canvas, int x, int y);

#endif // _CANVAS_H_
