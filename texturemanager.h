#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "selene.h"

typedef struct _textData textData;

typedef struct _textData {
  char * _name;
  GLuint _tex;
  textData * _next;
} textData;

void selene_add_text_data(const char * name, GLuint tex);

void selene_find_text_data(const char * name);

typedef struct {
  textData * _data;
  char _current_texture[256];
  GLuint _current_ID;
} TextureManager;

TextureManager * texture_manager;

void selene_init_texture_manager();

void selene_bind_texture(const char * texture);

void selene_unbind_texture();

#endif // _TEXTUREMANAGER_H_
