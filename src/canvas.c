#include "canvas.h"

Canvas * selene_create_canvas(int width, int height) {
  Canvas* canvas = calloc(1, sizeof(Canvas));

  canvas->_width = width;
  canvas->_height = height;

  /*float vertices[] = {
    -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };*/
  float vertices[] = {
    -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
  };
  

  glGenVertexArrays(1, &(canvas->_vao));
  glGenBuffers(1, &(canvas->_vbo));

  glBindVertexArray(canvas->_vao);
  glBindBuffer(GL_ARRAY_BUFFER, canvas->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
  
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);

  glGenFramebuffers(1, &(canvas->_fbo));
  glBindFramebuffer(GL_FRAMEBUFFER, canvas->_fbo);

  canvas->_texture = selene_gen_attach_texture(0, 0, width, height);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, canvas->_texture, 0);

  /*glGenRenderbuffers(1, &(canvas->_rbo));
  glBindRenderbuffer(GL_RENDERBUFFER, canvas->_rbo);

  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, canvas->_rbo);*/

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    printf("Framebuffer is not complete\n");
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  

  return canvas;
}

GLuint selene_gen_attach_texture(GLboolean depth, GLboolean stencil, int width, int height) {
  GLenum attachment_type;
  if (!depth && !stencil)
    attachment_type = GL_RGBA;
  else if (depth && !stencil)
    attachment_type = GL_DEPTH_COMPONENT;
  else if(!depth && stencil)
    attachment_type = GL_STENCIL_INDEX;

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  if (!depth && !stencil) {
    glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, width, height, 0, attachment_type, GL_UNSIGNED_BYTE, 0);
  }
  else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  return texture;
}

void selene_set_canvas(Canvas * canvas) {
  if (canvas) {
    glBindFramebuffer(GL_FRAMEBUFFER, canvas->_fbo);
    glViewport(0, 0, canvas->_width, canvas->_height);
  }
  else {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 640, 480);
  }
}

void selene_draw_canvas(Canvas * canvas, int x, int y) {
  selene_use_default_shader();
  mat4x4 model;
  mat4x4_identity(model);
  mat4x4_translate(model, canvas->_width/2 + x, canvas->_height/2 + y, 0);

  mat4x4_scale_aniso(model, model, canvas->_width/2, canvas->_height/2, 0.0f);

  vec4 tex;
  tex[0] = 0.0f;
  tex[1] = 0.0f;
  tex[2] = 1.0f;
  tex[3] = 1.0f;

  selene_send_uniform(CORE->_default_shader, "model", 16, *model);
  selene_send_uniform(CORE->_default_shader, "spriteFrame", 4, tex);

  glBindTexture(GL_TEXTURE_2D, canvas->_texture);
  glBindVertexArray(canvas->_vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
