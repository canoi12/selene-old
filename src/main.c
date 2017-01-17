#include <stdio.h>

#include "selene.h"

#define NIMAGES 100

typedef struct image_vector Vector;

typedef struct image_vector {
  Image * image;
  Vector * next;
} Vector;

void insert_vector(Vector * vec, Image * image) {
  Vector * aux;
  aux = vec;
  while(aux->next != NULL) {
    aux = aux->next;
  }
  Vector * newvec = malloc(sizeof(Vector));
  newvec->image = image;
  newvec->next = NULL;
  aux->next = newvec;
}

void draw_values(Vector * vec) {
  int x=0, y=-1;
  Vector * aux;
  aux = vec->next;
  while(aux->next != NULL) {
    Quad quad = {0, 0, (640/NIMAGES), (480/NIMAGES)};
    x = x % NIMAGES;
    if (x == 0) {
      y++;
    }
    selene_draw_image(aux->image, &quad, x *  (640/NIMAGES), y * (480/NIMAGES));
    x++;
    aux = aux->next;
  }
}

typedef struct player {
  int _x;
  int _y;
  int _width;
  int _height;
  Image* _image;
  Quad* _quad;
} Player;

void init_player(Player* player) {
  player->_image = selene_create_image("src/assets/astronaut.png");
}

void update_player(Player* player) {

}

int main(int argc, char* argv[]) {

  selene_init(640, 480, SDL_WINDOW_OPENGL);

  Image * img = selene_create_image("src/assets/astronaut.png");
  Image * img2 = selene_create_image("src/assets/bg_sky.png");
  SDL_Color color = {255, 255, 255, 255};
  Font * font = selene_create_font("src/assets/Early GameBoy.ttf", 16, color);
  
  glClearColor(0.2, 0.3, 0.3, 1.0);
  
  int frames = 0;
  Uint32 starttime = SDL_GetTicks();

  float frametime = 0.0f;

  Quad quad[] = {
    {0, 16, 16, 16},
    {16, 16, 16, 16},
    {32, 16, 16, 16},
    {48, 16, 16, 16},
    {64, 16, 16, 16}
  };

  int frame = 0;

  int x=320, y=240;
  float flip = 1.0f;

  SpriteBatch * batch = selene_create_sprite_batch(img2, 1000000);

  int ys = 0;
  int xs = 0;
  for (int j = 0; j < 500; j++) {
    int xs = 0;
    for (int i = 0; i < 500; i++) {
      Quad qt = {0, 0, 128, 128};
      if (i % 100 == 0) {
	xs += 4;
      }
      selene_sprite_batch_add(batch, &qt, i * (128 + xs), j * (128 + ys));
    }
    if (j % 100 == 0) {
      ys += 4;
    }
  }

  float scalex = 1.0f;
  float scaley = 1.0f;

  selene_set_font(font);

  int numOfSegs = 1000;
  float radius = 160;

  float segmentsx[(numOfSegs + 2)];
  float segmentsy[(numOfSegs + 2)];

  GLfloat doublePi = M_PI * 2.0f;
  segmentsx[0] = x;
  segmentsy[0] = y;
    

  for (int i = 0; i < (numOfSegs + 2); i++) {
    float theta = (doublePi * i) / (float)(numOfSegs + 2);
    segmentsx[i] = x + (radius * cos(theta));
    segmentsy[i] = y + (radius * sin(theta));
  }

  float segments[(numOfSegs + 2) * 2];

  for (int i = 0; i < (numOfSegs + 2); i++) {
    segments[i * 2] = segmentsx[i];
    segments[(i * 2) + 1] = segmentsy[i];
  }

  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(segments), segments, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  vec2 p0 = {64, 64};
  vec2 p1 = {74, 156};
  vec2 p2 = {156, 74};
  vec2 p3 = {256, 256};

  int xb, yb;

  Bezier* bezier = selene_create_bezier(p0, p1, p2, p3);
  
  while (CORE->_running) {
    selene_poll_event();

    if (CORE->_event.type == SDL_QUIT) {
      CORE->_running = SELENE_FALSE;
    }

    if (selene_key_down("left")) {
      x -= 4;
      flip = -1.0f;
    }
    if (selene_key_down("right")) {
      x += 4;
      flip = 1.0f;
    }
    if (selene_key_down("up")) {
      y -= 4;
    }
    if (selene_key_down("down")) {
      y += 4;
    }
    
    if (selene_key_down("A")) {
      scalex -= 0.01f;
      scaley -= 0.01f;
    } else if(selene_key_down("D")) {
      scalex += 0.01f;
      scaley += 0.01f;
    }
    // Clear the screen
    selene_clear_screen();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    selene_use_default_shader();

    frametime += 0.1f;
    if (frametime >= 0.6f) {
      frametime = 0.f;
      frame += 1;
      if (frame >= 5) {
	frame = 0;
      }
    }

    selene_translate_camera(0, 0);
    selene_scale_camera(scalex, scalex);
    //draw_values(vec);
    //printf("%d\n", frame);
    Quad * q;
    q = quad + frame;
    //for (int i = 0; i < 250000; i++)
    //selene_draw_image_ex(img, NULL, 0, 32, 4.0 * flip, 4.0, 0, 8, 8);

    //selene_sprite_batch_draw(batch);

    //selene_draw_circle("filled", x, 64, 32, 20);
    selene_draw_bezier_curve(bezier, 100, 1);

    ++frames;

    Uint32 currenttime = SDL_GetTicks() - starttime;
    if (currenttime) {
      double seconds = currenttime / 1000.0;
      double fps = frames / seconds;
      //printf("%f FPS\n", fps);
      char * fps_text = malloc(sizeof(char) * 5);
      sprintf(fps_text, "%f", fps);
      selene_print_text(fps_text, 0, 0);
    }
    glDisable(GL_BLEND);
    selene_swap_window();
  }

  selene_destroy_image(img);
  selene_destroy_sprite_batch(batch);
  selene_terminate();

  return 0;
}
