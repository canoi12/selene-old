#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image * selene_create_image(const char * path) {
  Image * image = (Image*) malloc(sizeof(Image));  
  
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
  
  glGenVertexArrays(1, &(image->_vao));
  glBindVertexArray(image->_vao);

  glGenBuffers(1, &(image->_vbo));
  
  glBindBuffer(GL_ARRAY_BUFFER, image->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glGenBuffers(1, &(image->_ebo));
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, image->_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) (2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) (5 * sizeof(float)));
  glEnableVertexAttribArray(2);
  
  glBindVertexArray(0);

  // Textures
  
  glGenTextures(1, &(image->_tex));

  glBindTexture(GL_TEXTURE_2D, image->_tex);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int w, h, comp;
  unsigned char * img = stbi_load(path, &(image->_width), &(image->_height), &comp, STBI_rgb_alpha);

  if (!img) {
    printf("Could not be possible to load the image: %s\n", path);
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->_width, image->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

  stbi_image_free(img);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  return image;
}

int selene_get_image_width(Image * image) {
  return image->_width;
}

int selene_get_image_height(Image * image) {
  return image->_height;
}

void selene_draw_image(Image * image, Quad * quad, int x, int y) {

  mat4x4 model;

  mat4x4_translate(model, x, y, 0.0);

  vec4 tex;
  if (quad) {

    for (int i = 0; i < 4; i++) {
      float d = i % 2 == 0 ? (float)selene_get_image_width(image) : (float) selene_get_image_height(image);
      tex[i] = (float)quad->_attr[i] / d;
    }
    
    mat4x4_scale_aniso(model, model, quad->_width, quad->_height, 0.0f);
  } else {
    tex[0] = 0.0f;
    tex[1] = 0.0f;

    tex[2] = 1.0f;
    tex[3] = 1.0f;
    mat4x4_scale_aniso(model, model, selene_get_image_width(image), selene_get_image_height(image), 0.0f);
  }
  
  selene_send_uniform(CORE->_default_shader, "model", 16, *model);
  selene_send_uniform(CORE->_default_shader, "spriteFrame" , 4, tex);
  
  glBindTexture(GL_TEXTURE_2D, image->_tex);
  glBindVertexArray(image->_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void selene_draw_image_ex(Image * image, Quad * quad, int x, int y, float sx, float sy, float angle, float cx, float cy) {
  mat4x4 model;
  mat4x4 aux;

  mat4x4_translate(model, x, y, 0.0);

  mat4x4_rotate_Z(model, model, toRadians(angle));
  mat4x4_translate_mul(model, -cx * sx, -cy * sy, 0.0);
  
  vec4 tex;
  if (quad) {

    for (int i = 0; i < 4; i++) {
      float d = i % 2 == 0 ? (float)selene_get_image_width(image) : (float) selene_get_image_height(image);
      tex[i] = (float)quad->_attr[i] / d;
    }
    
    mat4x4_scale_aniso(model, model, quad->_width * sx, quad->_height * sy, 0.0f);
  } else {
    tex[0] = 0.0f;
    tex[1] = 0.0f;

    tex[2] = 1.0f;
    tex[3] = 1.0f;
    mat4x4_scale_aniso(model, model, selene_get_image_width(image) * sx, selene_get_image_height(image) * sy, 0.0f);
  }
  
  selene_send_uniform(CORE->_default_shader, "model", 16, *model);
  selene_send_uniform(CORE->_default_shader, "spriteFrame" , 4, tex);
  

  glBindTexture(GL_TEXTURE_2D, image->_tex);
  glBindVertexArray(image->_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
