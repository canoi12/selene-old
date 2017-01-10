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

int main(int argc, char* argv[]) {

  selene_init(640, 480, SDL_WINDOW_OPENGL);

  Shader * shader = selene_create_shader("vert.glsl", "frag.glsl");
  
  //Image * image = selene_create_image("assets/astronaut.png");

  //Image image[2500];
  /*Vector * vec = malloc(sizeof(Vector));
  vec->next = NULL;

  Image * image = selene_create_image("assets/astronaut.png");
  for (int x = 0; x < (NIMAGES*NIMAGES); x++) {
    insert_vector(vec, image);
  }*/
  printf("wow\n");
  Image * img = selene_create_image("assets/843.jpg");
  
  glClearColor(0.2, 0.3, 0.3, 1.0);

  int x, y;
  float dy;

  int frames = 0;
  Uint32 starttime = SDL_GetTicks();
  
  while (engine->_running) {
    selene_poll_event();

    if (engine->_event.type == SDL_QUIT) {
      engine->_running = SELENE_FALSE;
    }

    if (selene_key_down("left")) {
      printf("Key Left Pressed\n");
    }
    // Clear the screen
    selene_clear_screen();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    selene_use_default_shader();

    //draw_values(vec);
    Quad quad = {0, 0, 720, 960};
    selene_draw_image(img, NULL, 0, 0);
    
    glDisable(GL_BLEND);
    selene_swap_window();

    ++frames;

    Uint32 currenttime = SDL_GetTicks() - starttime;
    if (currenttime) {
      double seconds = currenttime / 1000.0;
      double fps = frames / seconds;
      printf("%f FPS\n", fps);
    }
  }

  selene_terminate();

  return 0;
}
