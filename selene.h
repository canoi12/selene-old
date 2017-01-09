#ifndef _SELENE_H_
#define _SELENE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "linmath.h"

#include "window.h"
#include "shader.h"
#include "image.h"
#include "quad.h"

#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)
#define clamp(x, v1, v2) (min(v2, max(x, v1)))
#define toRadians(x) (x * (M_PI / 180.0))
#define toDegrees(x) (x * (180.0 / M_PI))

typedef enum {
  SELENE_TRUE = 1,
  SELENE_FALSE = 0
} sel_bool;

typedef struct window_s Window;
typedef struct shader_s Shader;

typedef struct selene_s {
  Window * _window;
  SDL_GLContext * _context;
  const Uint8 * _keyArray;
  SDL_Event _event;
  sel_bool _running;
  Shader * _default_shader;
} Selene;

Selene * engine;

void selene_init(int width, int height, GLenum flags);

void selene_init_data();

sel_bool selene_is_running();

void selene_poll_event();

void selene_clear_screen();

void selene_swap_window();

int selene_key_down(const char * key);

int selene_key_up(const char * key);

void selene_use_default_shader();

void selene_terminate();

#endif // _SELENE_H_