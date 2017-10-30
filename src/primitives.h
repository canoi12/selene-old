#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include "selene.h"

typedef struct circle {
  float _segments[52];
  GLuint _vao, _vbo;
} Circle;

typedef struct rectangle {
  float _vertices[8];
  int _indices[6];
  GLuint _vao, _vbo, _ebo;
} Rectangle;

typedef struct triangle {
  float vertices[6];
  GLuint _vao, _vbo;
} Triangle;

typedef struct line {
  float points[4];
  GLuint _vao, _vbo;
} Line;

typedef struct pixel {
  float point[2];
  GLuint _vao, _vbo;
} Pixel;

typedef struct bezier {
  vec2 _p[4];
} Bezier;

Circle* circle;
Rectangle* rectangle;
Triangle* triangle;
Line* line;
Pixel* pixel;

void selene_init_primitives();

void selene_draw_circle(const char* filled, int x, int y, float radius, int numOfSides);

void selene_draw_rectangle(const char* filled, int x, int y, float width, float height);

void selene_draw_rectangle_quad(const char* filled, Quad quad);

void selene_draw_triangle(const char* filled, int x1, int y1, int x2, int y2, int x3, int y3);

void selene_draw_line(int x1, int y1, int x2, int y2);

void selene_draw_point(int x, int y);

void selene_draw_bezier_curve(Bezier* bezier, float segments, int drawpoints);

void selene_draw_bezier_path(Bezier* bezier, float segments, int drawpoints, int size);

void selene_calculate_bezier_curve(float t, Bezier* bezier, int *x, int *y);

Bezier* selene_create_bezier(vec2 p1, vec2 p2, vec2 p3, vec4 p4);

#endif // _PRIMITIVES_H_
