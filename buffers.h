#ifndef _BUFFERS_H_
#define _BUFFERS_H_

#include "selene.h"

typedef struct {
  GLuint _vao;
} vao_buffer;

typedef struct {
  GLuint _vbo;
} vbo_buffer;

typedef struct {
  GLuint _ebo;
} ebo_buffer;

typedef struct {
  GLuint tex_buffer;
} tex_buffer;

vao_buffer * selene_create_vao();

vbo_buffer * selene_create_vbo(float * vertices, int size_of_data);

ebo_buffer * selene_create_ebo(int * indices, int size_of_data);

tex_buffer * selene_create_tex(unsigned char * image, GLenum filter, GLenum wrap);


#endif // _BUFFERS_H_
