#include "window.h"

Window * selene_create_window(const char * title, int width, int height, Uint32 flags) {
  Window * window = (Window*) malloc(sizeof(Window));

  window->_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

  window->_title = calloc(50, sizeof(char));

  //window->_title = title;
  strcpy(window->_title, title);
  window->_width = width;
  window->_height = height;

  return window;
}

void selene_resize_window(int width, int height) {
  SDL_SetWindowSize(CORE->_window->_window, width, height);
  glViewport(0, 0, width, height);
  CORE->_window->_width = width;
  CORE->_window->_height = height;
}

void selene_toggle_fullscreen() {
  if (SDL_GetWindowFlags(CORE->_window->_window) & SDL_WINDOW_FULLSCREEN) {
    SDL_SetWindowFullscreen(CORE->_window->_window, 0);
  } else {
    SDL_SetWindowFullscreen(CORE->_window->_window, SDL_WINDOW_FULLSCREEN);
  }
}

int selene_get_window_width() {
  return CORE->_window->_width;
}

int selene_get_window_height() {
  return CORE->_window->_height;
}

void selene_set_window_title(const char * title) {
  SDL_SetWindowTitle(CORE->_window->_window, title);
  strcpy(CORE->_window->_title, title);
  //CORE->_window->_title = title;
}

void selene_destroy_window(Window * window) {
  SDL_DestroyWindow(window->_window);
  free((void*)window->_title);
  free((void*)window);
}
