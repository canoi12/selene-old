#include "font.h"

int roundA(double x) {
  return (int)(x + 0.5);
}

int nextpoweroftwo(int x) {
  double logbase2 = log(x) / log(2);
  return roundA(pow(2, ceil(logbase2)));
}

Font * selene_create_font(const char * path, int size, SDL_Color color) {
  Font * font = malloc(sizeof(Font));
  font->_font = TTF_OpenFont(path, size);

  if (font->_font == NULL) {
    printf("Could not be possible to load the font\n");
  }

  /*font->_color.r = color.r;
  font->_color.g = color.g;
  font->_color.b = color.b;
  font->_color.a = color.a;*/
  font->_color = color;

  float vertices[] = {
    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };
  
  glGenVertexArrays(1, &(font->_vao));
  glGenBuffers(1, &(font->_vbo));
  glGenBuffers(1, &(font->_ebo));

  glBindVertexArray(font->_vao);
  
  glBindBuffer(GL_ARRAY_BUFFER, font->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, font->_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) (sizeof(float) * 2));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) (sizeof(float) * 5));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  return font;
}

void selene_set_font(Font * font) {
  CORE->_current_font = font;
}

void selene_set_font_color(SDL_Color color) {
  CORE->_current_font->_color = color;
}

void selene_print_text(const char * text, int x, int y) {
  selene_use_default_shader();
  
  SDL_Surface * surface = TTF_RenderText_Blended(CORE->_current_font->_font, text, CORE->_current_font->_color);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  int w, h;
  w = nextpoweroftwo(surface->w);
  h = nextpoweroftwo(surface->h);
  SDL_Surface * s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

  SDL_BlitSurface(surface, 0, s, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);


  mat4x4 model;
  mat4x4_translate(model, x, y, 0.0f);
  mat4x4_scale_aniso(model, model, surface->w, surface->h, 0.0f);

  vec4 spriteFrame;
  spriteFrame[0] = 0.0f;
  spriteFrame[1] = 0.0f;
  spriteFrame[2] = 1.0f;
  spriteFrame[3] = 1.0f;
  
  selene_send_uniform(CORE->_default_shader, "model", 16, *model);
  selene_send_uniform(CORE->_default_shader, "spriteFrame", 4, spriteFrame);

  glBindVertexArray(CORE->_current_font->_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  SDL_FreeSurface(surface);
  SDL_FreeSurface(s);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void selene_destroy_font(Font* font) {
  TTF_CloseFont(font->_font);
  glDeleteVertexArrays(1, &(font->_vao));
  glDeleteBuffers(1, &(font->_vbo));
  glDeleteBuffers(1, &(font->_ebo));
  free(font);
}
