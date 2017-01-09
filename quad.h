#ifndef _QUAD_H_
#define _QUAD_H_

typedef union quad_s {
  struct {
    int _x;
    int _y;
    int _width;
    int _height;
  };
  int _attr[4];
} Quad;

#endif // _QUAD_H_
