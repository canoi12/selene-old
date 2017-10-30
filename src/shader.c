#include "shader.h"

Shader * selene_create_shader(const char * path) {
  Shader * shader = malloc(sizeof(Shader));

  ShaderProgramSource source = selene_parse_shader(path);
  printf("test %s\n", source.VertexSource);
  printf("test %s\n", source.FragmentSource);

  GLuint vertex_shader = selene_load_shader(source.VertexSource, GL_VERTEX_SHADER);
  GLuint fragment_shader = selene_load_shader(source.FragmentSource, GL_FRAGMENT_SHADER);

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

ShaderProgramSource selene_parse_shader(const char * path) {
  FILE * fp;
  char * line;
  size_t len = 0;
  ssize_t read;
  enum {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
  } ShaderType;

  char * ss[2];
  ss[0] = malloc(sizeof(char) * 2048);
  ss[1] = malloc(sizeof(char) * 2048);
  ss[0][0] = '\0';
  ss[1][0] = '\0';
  int tp = NONE;

  fp = fopen(path, "r");
  if (fp == NULL)
    exit(1);
  
  while ((read = getline(&line, &len, fp)) != -1) {
    if (strstr(line, "#shader") != NULL) {
      if (strstr(line, "vertex")) {
        tp = VERTEX;
      } else if (strstr(line, "fragment")) {
        tp = FRAGMENT;
      }
    } else {
      //printf("%d line: %s\n", tp, line);
      strcat(ss[tp], line);
    }
  }

  return (ShaderProgramSource){ ss[0], ss[1] };
}

GLuint selene_load_shader(const char * source, GLenum type) {
 //const char * buffer = selene_load_shader_source(path);

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
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

  if (!fp) {
    printf("Não foi possível carregar o shader: %s\n", path);
    exit(0);
  }
  
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
  if (shader) {
    CORE->_current_shader = shader;
  } else {
    CORE->_current_shader = CORE->_default_shader;
  }
  glUseProgram(CORE->_current_shader->_ID);
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

void selene_delete_shader(Shader* shader) {
  free(shader);
}
