#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "selene.h"

typedef struct window {
  SDL_Window * _window;
  const char * _title;
  int _width;
  int _height;
  Uint32 _flags;
} Window;

Window * selene_create_window(const char * title, int width, int height, Uint32 flags);

void selene_resize_window(int width, int height);

void selene_toggle_fullscreen();

int selene_get_window_width();

int selene_get_window_height();

void selene_set_window_title(const char * title);

#endif // _WINDOW_H_
