#include <stdio.h>

#include "selene.h"

#define NIMAGES 100

extern mat4x4 world;
extern mat4x4 view;


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
  float _dx;
  float _dy;
  float _gravity;
  int _width;
  int _height;
  float _angle;
  int _flip;
  int _centerx;
  int _centery;
  Image* _image;
  Quad* _quad;
  Quad _collision;
  float _frametime;
  int _animation;
  Quad* _anim;
  int _frame;
} Player;

void create_anim(Image* image, Quad** quad, int frame_size, int n_images) {
  int w = selene_get_image_width(image) / frame_size;
  int h = selene_get_image_height(image) / frame_size;

  Quad* q = *quad;
  q = calloc(n_images, sizeof(Quad));

  int x = 0;
  int y = -1;

  for (int i = 0; i < n_images; i++) {
    x = i % w;
    if (x == 0) {
      ++y;
    }
    q[i]._x = x * frame_size;
    q[i]._y = y * frame_size;
    q[i]._width = frame_size;
    q[i]._height = frame_size;
  }

  *quad = q;
}

int collision(Quad q1, Quad q2) {
  if (q1._x < q2._x + q2._width &&
      q1._x + q1._width > q2._x &&
      q1._y < q2._y + q2._height &&
      q1._y + q1._height > q2._y)
    return 1;
  return 0;
}

void init_player(Player* player) {
  player->_image = selene_create_image("src/assets/bear.png");
  player->_x = 0;
  player->_y = 128;
  player->_dx = 0.0f;
  player->_dy = 0.0f;
  player->_gravity = 800.0f;
  player->_width = 32;
  player->_height = 32;

  player->_collision._attr[0] = 0;
  player->_collision._attr[1] = 0;
  player->_collision._attr[2] = 32;
  player->_collision._attr[3] = 32;
  
  //player->_quad = calloc(9, sizeof(Quad));

  player->_anim = calloc(2, sizeof(Quad));
  player->_anim[0]._x = 0;
  player->_anim[0]._y = 4;

  player->_anim[1]._x = 4;
  player->_anim[1]._y = 9;
  
  player->_angle = 0.0f;
  player->_flip = 1;
  player->_centerx = 16;
  player->_centery = 16;

  player->_frametime = 0.0f;
  player->_frame = 0;

  create_anim(player->_image, &(player->_quad), 32, 13);
}

void update_player(Player* player, double delta) {

  if (selene_key_down("left")) {
    player->_dx = -200.0f * delta;
    player->_animation = 1;
    player->_flip = -1;
  }
  else if(selene_key_down("right")) {
    player->_dx = 200.0f * delta;
    player->_animation = 1;
    player->_flip = 1;
  } else {
    player->_animation = 0;
    player->_dx = 0.0f;
  }

  if (player->_y + (player->_dy * delta) < 128) {
    player->_dy += player->_gravity * delta;
  } else {
    player->_dy = 0;
  }

  if (selene_key_down("up")) {
    player->_dy = -200;
  }

  player->_collision._attr[0] = player->_x - player->_centerx + player->_dx;
  player->_collision._attr[1] = player->_y - player->_centery + (player->_dy * delta);
  player->_collision._attr[2] = 32;
  player->_collision._attr[3] = 32;
  
  
  player->_frametime += 0.1f;
  if (player->_frametime >= 0.4f) {
    player->_frametime = 0.f;
    player->_frame += 1;
    if (player->_frame >= player->_anim[player->_animation]._y) {
      player->_frame = 0;
    }
  }

  player->_x += player->_dx;
  player->_y += player->_dy * delta;
  
}

void draw_player(Player* player) {
  Quad* q;
  q = player->_quad + ((int)player->_anim[player->_animation]._x) + player->_frame;
  //printf("%d %d %d %d\n", q->_x, q->_y, q->_width, q->_height);
  selene_draw_image_ex(player->_image, q, player->_x, player->_y, player->_flip, 1.0f, player->_angle, player->_centerx, player->_centery);
}

int main(int argc, char* argv[]) {
  
  selene_init(640, 480, SDL_WINDOW_OPENGL);

  Vertex * vertex;

  Image * img = selene_create_image("src/assets/bear.png");
  Image * img2 = selene_create_image("src/assets/bg_sky.png");
  SDL_Color color = {255, 255, 255, 255};
  Font * font = selene_create_font("src/assets/Early GameBoy.ttf", 16, color);
  
  glClearColor(0.2, 0.3, 0.3, 1.0);
  
  int frames = 0;
  Uint32 starttime = SDL_GetTicks();

  float frametime = 0.0f;

  int frame = 0;

  int x=320, y=240;
  float flip = 1.0f;

  SpriteBatch * batch = selene_create_sprite_batch(img2, 1000);
  //Shader * waveShader = selene_create_shader("src/shaders/water.vert", DEFAULT_FRAG_SHADER_PATH);

  Canvas* canvas = selene_create_canvas(320, 240);

  int ys = 0;
  int xs = 0;
  for (int j = 0; j < 10; j++) {
    int xs = 0;
    for (int i = 0; i < 10; i++) {
      Quad qt = {0, 0, 32, 32};
      selene_sprite_batch_add(batch, &qt, i * (32 + xs), j * (32 + ys));
    }
  }

  float scalex = 1.0f;
  float scaley = 1.0f;

  selene_set_font(font);

  vec2 p0 = {64, 64};
  vec2 p1 = {74, 156};
  vec2 p2 = {156, 74};
  vec2 p3 = {256, 256};

  int xb, yb;

  Bezier* bezier = selene_create_bezier(p0, p1, p2, p3);

  Player* player;
  player = malloc(sizeof(Player));
  init_player(player);

  Quad q = {x + 64, 32, 128, 128};
  double seconds = 0.0;

  float angleWave = 0.0f;
  float amplitudeWave = 0.1f;
  
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
    glClearColor(0.2, 0.3, 0.3, 1.0);
    selene_clear_screen();
    
    selene_set_canvas(canvas);
    // Clear the screen
    glClearColor(1.0, 0.0, 0.0, 0.0);
    selene_clear_screen();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    selene_use_shader(NULL);

    selene_translate_camera((-player->_x + 320)*scalex, (-player->_y + 240)*scaley);
    //selene_translate_camera(0, 0);
    selene_scale_camera(scalex, scaley);
    
    //selene_draw_circle("filled", 0, 0, 32, 8);
    int olddx = player->_x;
    int olddy = player->_y;
    
    update_player(player, seconds);

    if (collision(player->_collision, q)) {
      player->_x = olddx;
      player->_y = olddy;
      player->_dy = 0;
    }

    selene_draw_rectangle_quad("line", q);
    selene_draw_rectangle_quad("line", player->_collision);

    draw_player(player);

    selene_draw_image(img2, NULL, 320, 240);
    selene_set_canvas(NULL);

    //selene_draw_image(img2, NULL, 0, 0);
    selene_translate_camera(0, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //selene_draw_canvas(canvas, 0, 0);
    //selene_draw_canvas(canvas, 320, 0);

    angleWave += seconds * 5.0f;
    while(angleWave > (M_PI*2))
      angleWave -= (M_PI*2);
    
    //selene_use_shader(waveShader);

    amplitudeWave = 5.0f;
    vec2 waveData = {angleWave, amplitudeWave};
    
    //selene_send_uniform(waveShader, "waveData", 2, waveData);
    //selene_send_uniform(waveShader, "view", 16, *view);
    //selene_send_uniform(waveShader, "world", 16, *world);
    selene_sprite_batch_draw(batch);

    selene_use_shader(NULL);
    selene_draw_canvas(canvas, 320, 0);
    
    ++frames;

    Uint32 endtime = SDL_GetTicks();

    Uint32 currenttime = endtime - starttime;
    if (currenttime) {
      seconds = currenttime / 1000.0;
      //printf("%f\n", seconds);
      //double fps = frames / seconds;
      double fps = 1.0f/seconds;
      //printf("%f FPS\n", fps);
      char * fps_text = malloc(sizeof(char) * 5);
      sprintf(fps_text, "%f", fps);
      selene_print_text(fps_text, 0, 0);
      starttime = endtime;
    }
    glDisable(GL_BLEND);
    selene_swap_window();
  }

  selene_destroy_image(img);
  selene_destroy_sprite_batch(batch);
  selene_terminate();

  return 0;
}
