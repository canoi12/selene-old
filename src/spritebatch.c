#include "spritebatch.h"

SpriteBatch * selene_create_sprite_batch(Image * image, int maxSprites) {
  SpriteBatch * batch = malloc(sizeof(SpriteBatch));
  batch->_maxSprites = maxSprites;

  glGenVertexArrays(1, &(batch->_vao));
  glGenBuffers(1, &(batch->_vbo));
  //glGenBuffers(1, &(batch->_ebo));
  batch->_image = image;

  glBindVertexArray(batch->_vao);
  glBindBuffer(GL_ARRAY_BUFFER, batch->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maxSprites * 28, NULL, GL_STREAM_DRAW);

  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->_ebo);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * maxSprites, NULL, GL_STREAM_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) (2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) (5 * sizeof(float)));
  glEnableVertexAttribArray(2);
  
  glBindVertexArray(0);
  
  return batch;
}

void selene_sprite_batch_add(SpriteBatch * batch, Quad * quad, int x, int y) {
  /*float vertices[] = {
    x/640.0f, y/480.0f, 1.0f, 1.0f, 1.0f, quad->_x/640.0f, quad->_y/480.0f,
    x/640.0f, (y + quad->_height)/480.0f, 1.0f, 1.0f, 1.0f, quad->_x/640.0f, (quad->_y + quad->_height)/480.0f,
    (x + quad->_width)/640.0f, (y + quad->_height)/480.0f, 1.0f, 1.0f, 1.0f, (quad->_x + quad->_width)/640.0f, (quad->_y + quad->_height)/480.0f,
    (x + quad->_width)/640.0f, y/480.0f, 1.0f, 1.0f, 1.0f, (quad->_x + quad->_width)/640.0f, (quad->_y)/480.0f
    };*/

  Quad q = {0, 0, 0, 0};
  float qx = ((float)quad->_x / (float)selene_get_image_width(batch->_image));
  float qy = ((float)quad->_y / (float)selene_get_image_height(batch->_image));

  float qw = ((float)quad->_width / (float)selene_get_image_width(batch->_image));
  float qh = ((float)quad->_height / (float)selene_get_image_height(batch->_image));

  float vx = (float)x / (float)(selene_get_window_width());
  float vy = (float)y / (float)(selene_get_window_height());

  //printf("%d %d\n", x, y);
  //printf("%f\n", qx);

  /*float vertices[] = {
    x, y, 1.0f, 1.0f, 1.0f, quad->_x, quad->_y,
    x, (y + quad->_height), 1.0f, 1.0f, 1.0f, quad->_x, (quad->_y + quad->_height),
    (x + quad->_width), (y + quad->_height), 1.0f, 1.0f, 1.0f, (quad->_x + quad->_width), (quad->_y + quad->_height),

    x, y, 1.0f, 1.0f, 1.0f, quad->_x, quad->_y,
    x + quad->_width, y, 1.0f, 1.0f, 1.0f, quad->_x + quad->_width, quad->_y,
    (x + quad->_width), y + quad->_height, 1.0f, 1.0f, 1.0f, (quad->_x + quad->_width), (quad->_y + quad->_height)
  };*/

  float vertices[] = {
    x, y, 1.0f, 1.0f, 1.0f, qx, qy,
    x, (y + quad->_height), 1.0f, 1.0f, 1.0f, qx, (qy + qh),
    (x + quad->_width), (y + quad->_height), 1.0f, 1.0f, 1.0f, (qx + qw), (qy + qh),

    x, y, 1.0f, 1.0f, 1.0f, qx, qy,
    x + quad->_height, y, 1.0f, 1.0f, 1.0f, qx + qw, qy,
    (x + quad->_width), y + quad->_height, 1.0f, 1.0f, 1.0f, (qx + qw), (qy + qh)
    };

  

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  glBindVertexArray(batch->_vao);

  glBindBuffer(GL_ARRAY_BUFFER, batch->_vbo);
  if (batch->_currentSprites + 1 < batch->_maxSprites) {
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) * batch->_currentSprites, sizeof(vertices) , vertices);
  } else {
     printf("Sprite Batch cheio: %d\n", batch->_currentSprites);
  }

  /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->_ebo);
  if (batch->_currentSprites + 1 < batch->_maxSprites) {
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * batch->_currentSprites, sizeof(indices), indices);
    }*/

  glBindVertexArray(0);

  ++(batch->_currentSprites);
}

void selene_sprite_batch_draw(SpriteBatch * batch) {
  mat4x4 model;
  mat4x4_identity(model);

  //mat4x4_scale_aniso(model, model, 64.0f, 64.0f, 0.0f);

  vec4 text_coord;
  text_coord[0] = 0.0f;
  text_coord[1] = 0.0f;
  text_coord[2] = 1.0f;
  text_coord[3] = 1.0f;

  selene_send_uniform(CORE->_current_shader, "model", 16, *model);
  selene_send_uniform(CORE->_current_shader, "spriteFrame", 4, text_coord);
  
  glBindTexture(GL_TEXTURE_2D, batch->_image->_tex);
  glBindVertexArray(batch->_vao);
  //glDrawElements(GL_TRIANGLES, batch->_currentSprites, GL_UNSIGNED_INT, 0);
  glDrawArrays(GL_TRIANGLES, 0, batch->_currentSprites * 6);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void selene_destroy_sprite_batch(SpriteBatch* batch) {
  glDeleteVertexArrays(1, &(batch->_vao));
  glDeleteBuffers(1, &(batch->_vbo));
  glDeleteBuffers(1, &(batch->_ebo));
  selene_destroy_image(batch->_image);
  free(batch);
}
