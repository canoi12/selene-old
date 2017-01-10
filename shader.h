#ifndef _SHADER_H_
#define _SHADER_H_

#include "selene.h"

enum sel_uni_type {
  SELENE_VEC2 = 0,
  SELENE_VEC3 = 1,
  SELENE_VEC4 = 2,
  SELENE_MAT4 = 3,
  SELENE_FLOAT = 4,
  SELENE_INT = 5
};

typedef struct shader {
  GLuint _ID;
} Shader;

Shader * selene_create_shader(const char * vert_path, const char * frag_path);

GLuint selene_load_shader(const char * path, GLenum type);

char * selene_load_shader_source(const char * path);

void selene_use_shader(Shader * shader);

void selene_send_uniform(Shader * shader, const char * name, int size, const float * value);

#endif // _SHADER_H_
