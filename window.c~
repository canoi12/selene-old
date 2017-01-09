#include "window.h"

Window * selene_create_window(const char * title, int width, int height, Uint32 flags) {
  Window * window = (Window*) malloc(sizeof(Window));

  window->_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

  window->_title = title;
  window->_width = width;
  window->_height = height;

  return window;
}

void selene_resize_window(int width, int height) {
  SDL_SetWindowSize(engine->_window->_window, width, height);
  glViewport(0, 0, width, height);
  engine->_window->_width = width;
  engine->_window->_height = height;
}

void selene_toggle_fullscreen() {
  if (SDL_GetWindowFlags(engine->_window->_window) & SDL_WINDOW_FULLSCREEN) {
    SDL_SetWindowFullscreen(engine->_window->_window, 0);
  } else {
    SDL_SetWindowFullscreen(engine->_window->_window, SDL_WINDOW_FULLSCREEN);
  }
}

int selene_get_window_width() {
  return engine->_window->_width;
}

int selene_get_window_height() {
  return engine->_window->_height;
}

void selene_set_window_title(const char * title) {
  SDL_SetWindowTitle(engine->_window->_window, title);
  engine->_window->_title = title;
}
