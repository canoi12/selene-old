#include "shader.h"

Shader * selene_create_shader(const char * vert_path, const char * frag_path) {
  Shader * shader = malloc(sizeof(Shader));

  GLuint vertex_shader = selene_load_shader(vert_path, GL_VERTEX_SHADER);
  GLuint fragment_shader = selene_load_shader(frag_path, GL_FRAGMENT_SHADER);

  shader->_ID = glCreateProgram();
  
  glAttachShader(shader->_ID, vertex_shader);
  glAttachShader(shader->_ID, fragment_shader);

  glLinkProgram(shader->_ID);

  char infoLog[512];
  int success;
  glGetProgramiv(shader->_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader->_ID, 512, NULL, infoLog);
    printf("Shader Program error: %s\n", infoLog);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  
  return shader;
}

GLuint selene_load_shader(const char * path, GLenum type) {
  const char * buffer = selene_load_shader_source(path);

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &buffer, NULL);
  glCompileShader(shader);

  const char * shader_str = type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader";

  char infoLog[512];
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("%s error: %s\n", shader_str, infoLog);
  }

  return shader;
}

char * selene_load_shader_source(const char * path) {
  FILE * fp = fopen(path, "rb");

  size_t buffsize;
  fseek(fp, 0, SEEK_END);
  buffsize = ftell(fp);
  rewind(fp);

  char * buffer = malloc(sizeof(char) * (buffsize + 1));
  fread(buffer, 1, buffsize, fp);

  buffer[buffsize] = '\0';
  
  fclose(fp);

  return buffer;
}

void selene_use_shader(Shader * shader) {
  glUseProgram(shader->_ID);
}

void selene_send_uniform(Shader * shader, const char * name, int size, const float * value) {
  GLuint uniform = glGetUniformLocation(shader->_ID, name);

  switch (size) {
  case 1:
    glUniform1fv(uniform, 1, value);
    break;

  case 2:
    glUniform2fv(uniform, 1, value);
    break;

  case 3:
    glUniform3fv(uniform, 1, value);
    break;

  case 4:
    glUniform4fv(uniform, 1, value);
    break;

  case 16:
    glUniformMatrix4fv(uniform, 1, GL_FALSE, value);
    break;
  }
}
