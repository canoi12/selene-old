#ifndef _FONT_H_
#define _FONT_H_

#include "selene.h"

typedef struct font {
  TTF_Font * _font;
  SDL_Color _color;
  GLuint _vao, _vbo;
  GLuint _ebo;
} Font;

Font * selene_create_font(const char * path, int size, SDL_Color color);

void selene_set_font(Font * font);

void selene_set_font_color(SDL_Color color);

void selene_print_text(const char * text, int x, int y);

#endif // _FONT_H_
