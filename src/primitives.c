#include "primitives.h"

void selene_init_primitives() {
  circle = calloc(1, sizeof(Circle));
  glGenVertexArrays(1, &(circle->_vao));
  glGenBuffers(1, &(circle->_vbo));

  rectangle = calloc(1, sizeof(Rectangle));
  glGenVertexArrays(1, &(rectangle->_vao));
  glGenBuffers(1, &(rectangle->_vbo));
  glGenBuffers(1, &(rectangle->_ebo));

  triangle = calloc(1, sizeof(Triangle));
  glGenBuffers(1, &(triangle->_vao));
  glGenBuffers(1, &(triangle->_vbo));

  line = calloc(1, sizeof(Line));
  glGenVertexArrays(1, &(line->_vao));
  glGenBuffers(1, &(line->_vbo));

  pixel = calloc(1, sizeof(Pixel));
  glGenVertexArrays(1, &(pixel->_vao));
  glGenBuffers(1, &(pixel->_vbo));
}

void selene_draw_circle(const char* filled, int x, int y, float radius, int numOfSides) {
  selene_use_default_shader();
  int numOfVertices = 1;
  if (numOfSides)
    numOfVertices = numOfSides + 2;
  else
    numOfVertices = 52;
  mat4x4 model;
  mat4x4_identity(model);

  float pi2 = M_PI * 2.0f;

  selene_send_uniform(CORE->_default_shader, "model", 16, *model);

  float segmentsx[numOfVertices];
  float segmentsy[numOfVertices];

  for (int i = 0; i < numOfVertices; i++) {
    float theta = (i * pi2) / numOfVertices;
    segmentsx[i] = x + (radius * cos(theta));
    segmentsy[i] = y + (radius * sin(theta));
  }

  float segments[numOfVertices * 2];

  for (int i = 0; i < numOfVertices; i++) {
    segments[i * 2] = segmentsx[i];
    segments[(i * 2) + 1] = segmentsy[i];
  }


  glBindVertexArray(circle->_vao);
  glBindBuffer(GL_ARRAY_BUFFER, circle->_vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(segments), segments, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glBindVertexArray(circle->_vao);
  glDrawArrays(GL_TRIANGLE_FAN, 0, numOfVertices);

  glBindVertexArray(0);
}

void selene_draw_rectangle(const char* filled, int x, int y, float width, float height) {
  selene_use_default_shader();
  mat4x4 model;
  mat4x4_identity(model);

  selene_send_uniform(CORE->_default_shader, "model", 16, *model);
  float vertices[] = {
    x, y,
    x + width, y,
    x + width, y + height,
    x, y + height
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  glBindVertexArray(rectangle->_vao);

  glBindBuffer(GL_ARRAY_BUFFER, rectangle->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle->_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glBindVertexArray(rectangle->_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void selene_draw_triangle(const char* filled, int x1, int y1, int x2, int y2, int x3, int y3) {
  mat4x4 model;
  mat4x4_identity(model);

  selene_send_uniform(CORE->_default_shader, "model", 16, *model);

  float vertices[] = {
    x1, y1,
    x2, y2,
    x3, y3
  };

  glBindVertexArray(triangle->_vao);

  glBindBuffer(GL_ARRAY_BUFFER, triangle->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glBindVertexArray(triangle->_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

void selene_draw_line(int x1, int y1, int x2, int y2) {
  mat4x4 model;
  mat4x4_identity(model);
  selene_send_uniform(CORE->_default_shader, "model", 16, *model);
  float vertices[] = {
    x1, y1,
    x2, y2,
  };

  glBindVertexArray(line->_vao);

  glBindBuffer(GL_ARRAY_BUFFER, line->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glBindVertexArray(line->_vao);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}

void selene_draw_point(int x, int y) {
  mat4x4 model;
  mat4x4_identity(model);


  selene_send_uniform(CORE->_default_shader, "model", 16, *model);
  float vertices[] = {
    x, y,
  };

  glBindVertexArray(pixel->_vao);

  glBindBuffer(GL_ARRAY_BUFFER, pixel->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glBindVertexArray(pixel->_vao);
  glDrawArrays(GL_POINTS, 0, 1);
  glBindVertexArray(0);
}

void selene_draw_bezier_curve(Bezier* bezier, float segments, int drawpoints) {
  int xb, yb;
  int oxb, oyb;
  if (drawpoints) {
    selene_draw_circle(NULL, bezier->_p[0][0], bezier->_p[0][1], 2, 10);
    selene_draw_circle(NULL, bezier->_p[1][0], bezier->_p[1][1], 2, 10);
    selene_draw_circle(NULL, bezier->_p[2][0], bezier->_p[2][1], 2, 10);
    selene_draw_circle(NULL, bezier->_p[3][0], bezier->_p[3][1], 2, 10);
  }
  
  for(int i = 0; i < segments; i++) {
    selene_calculate_bezier_curve(((float)(i) / segments) - (1.0f/segments), bezier, &oxb, &oyb);
    selene_calculate_bezier_curve((float)(i) / segments, bezier, &xb, &yb);
    selene_draw_line(oxb, oyb, xb, yb);
  }
}

/*void selene_draw_bezier_path(Bezier* bezier, float segments, int drawpoints, int size) {
  int xb, yb;
  int oxb, oyb;
  if (drawpoints) {
    selene_draw_circle(NULL, bezier->_p[0][0], bezier->_p[0][1], 2, 10);
    selene_draw_circle(NULL, bezier->_p[1][0], bezier->_p[1][1], 2, 10);
    selene_draw_circle(NULL, bezier->_p[2][0], bezier->_p[2][1], 2, 10);
    selene_draw_circle(NULL, bezier->_p[3][0], bezier->_p[3][1], 2, 10);
  }

  int segsize = segments * size;
  Bezier* p = bezier;
  
  
  for(int i = 1; i < segsize; i++) {
    if (i % size == 0)
      p++;
    selene_calculate_bezier_curve(((float)(i) / segsize) - (1.0f/segsize), &p, &oxb, &oyb);
    selene_calculate_bezier_curve((float)(i) / segsize, &p, &xb, &yb);
    selene_draw_line(oxb, oyb, xb, yb);
  }
  }*/

void selene_calculate_bezier_curve(float t, Bezier* bezier, int *x, int *y) {
  float u = 1 - t;
  float tt = t*t;
  float uu = u*u;
  float uuu = uu*u;
  float ttt = tt*t;

  float aux = 0.f;
  vec2 vaux;

  vec2 p;
  vec2_scale(p, bezier->_p[0], uuu);
  aux = 3.0f * uu * t;
  vec2_scale(vaux, bezier->_p[1], aux);
  vec2_add(p, p, vaux);

  vaux[0] = 0.0f;
  vaux[1] = 0.0f;
  aux = 3.0f * u * tt;
  vec2_scale(vaux, bezier->_p[2], aux);
  vec2_add(p, p, vaux);

  vaux[0] = 0.0f;
  vaux[1] = 0.0f;
  vec2_scale(vaux, bezier->_p[3], ttt);
  vec2_add(p, p, vaux);

  *x = p[0];
  *y = p[1];
}

Bezier* selene_create_bezier(vec2 p0, vec2 p1, vec2 p2, vec2 p3) {
  Bezier* bezier = calloc(1, sizeof(Bezier));

  bezier->_p[0][0] = p0[0];
  bezier->_p[0][1] = p0[1];

  bezier->_p[1][0] = p1[0];
  bezier->_p[1][1] = p1[1];

  bezier->_p[2][0] = p2[0];
  bezier->_p[2][1] = p2[1];

  bezier->_p[3][0] = p3[0];
  bezier->_p[3][1] = p3[1];
  
  return bezier;
}
