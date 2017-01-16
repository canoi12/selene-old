#include "texturemanager.h"

void selene_add_text_data(const char * name, GLuint tex) {
  textData *p;
  p = texture_manager->_data;
  while(p->_next != NULL) {
    p = p->_next;
  }
  p->_next = malloc(sizeof(textData));
  p->_next->_name = (char*)name;
  p->_tex = tex;
  p->_next = NULL;

  strcpy(texture_manager->_current_texture, name);
  texture_manager->_current_ID = tex;
}

void selene_find_text_data(const char * name) {
  textData *p;
  p = texture_manager->_data;
  while (p->_next != NULL && p->_name != name) {
    p = p->_next;
  }

  if ((p->_next)) {
    strcpy(texture_manager->_current_texture, p->_name);
    texture_manager->_current_ID = p->_tex;
    return;
  }
  printf("Texture not exists\n");
}

void selene_init_texture_manager() {
  texture_manager = malloc(sizeof(TextureManager));
  texture_manager->_data = malloc(sizeof(textData));
  texture_manager->_data->_next = NULL;
  strcpy(texture_manager->_current_texture, "");
}

void selene_bind_texture(const char * texture) {
  if (texture != texture_manager->_current_texture) {
    selene_find_text_data(texture);
  }
  glBindTexture(GL_TEXTURE_2D, texture_manager->_current_ID);
}

void selene_unbind_texture() {
  glBindTexture(GL_TEXTURE_2D, 0);
}
