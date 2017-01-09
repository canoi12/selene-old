#include "selene.h"

void selene_init(int width, int height, Uint32 flags) {
  engine = (Selene*) malloc(sizeof(Selene));
  engine->_running = SELENE_TRUE;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    engine->_running = SELENE_FALSE;
    fprintf(stderr, "Failed to init SDL...\n");
    exit (EXIT_FAILURE);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  engine->_window = selene_create_window("Selene", width, height, flags);

  if (engine->_window == NULL) {
    engine->_running = SELENE_FALSE;
    fprintf(stderr, "Failed to create Window...\n");
    exit (EXIT_FAILURE);
  }
  
  engine->_context = SDL_GL_CreateContext(engine->_window->_window);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    engine->_running = SELENE_FALSE;
    fprintf(stderr, "Failed to init GLEW...\n");
    exit (EXIT_FAILURE);
  }
  
  glViewport(0, 0, engine->_window->_width, engine->_window->_height);

  if ( SDL_GL_SetSwapInterval(1) < 0) {
    printf("Your hardware don't support Vsync\n");
  }

  engine->_keyArray = SDL_GetKeyboardState(NULL);

  engine->_default_shader = selene_create_shader("vert.glsl", "frag.glsl");
}

void selene_init_data() {

}

sel_bool selene_is_running() {
  return engine->_running;
}

void selene_poll_event() {
  SDL_PollEvent(&(engine->_event));
}

void selene_clear_screen() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void selene_swap_window() {
  SDL_GL_SwapWindow(engine->_window->_window);
}

int selene_key_down(const char * key) {
  return engine->_keyArray[SDL_GetScancodeFromName(key)];
}

int selene_key_up(const char * key) {
  return !(engine->_keyArray[SDL_GetScancodeFromName(key)]);
}

void selene_use_default_shader() {
  mat4x4 world;
  mat4x4 view;

  mat4x4_ortho(world, 0.0, (float) selene_get_window_width(), (float) selene_get_window_height(), 0.0, 0.0, 1.0);

  mat4x4_identity(view);
  mat4x4_translate(view, 0, 0, 0);
  mat4x4_scale_aniso(view, view, 1.0f, 1.0f, 0.0f);

  selene_use_shader(engine->_default_shader);
  selene_send_uniform(engine->_default_shader, "world", 16, *world);
  selene_send_uniform(engine->_default_shader, "view", 16, *view);
}

void selene_terminate() {
  SDL_DestroyWindow(engine->_window->_window);
  SDL_GL_DeleteContext(engine->_context);
  free(engine->_window);
  free(engine);
  SDL_Quit();
}
