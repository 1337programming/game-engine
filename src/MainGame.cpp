#include "MainGame.h"
#include "Errors.h"
#include <iostream>
#include <string>


MainGame::MainGame() :
  _window(nullptr),
  _screenWidth(1024),
  _screenHeight(768),
  _gameState(GameState::PLAY),
  _time(0.0f) {

}

MainGame::~MainGame() {

}

void MainGame::run() {
  initSystems();

  _sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

  gameLoop();
}

void MainGame::initSystems() {
  // Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight,
                             SDL_WINDOW_OPENGL);

  if (_window == nullptr) {
    fatalError("SDL Window could not be created!");
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GLContext glContext = SDL_GL_CreateContext(_window);
  if (glContext == nullptr) {
    fatalError("SDL_GL Context could not be created!");
  }

  // Mac only
  GLuint vertexArrayID;
  glGenVertexArrays(1, &vertexArrayID);
  glBindVertexArray(vertexArrayID);

  // Print out OPENGL and Shading Language
  int glVersionMajor;
  int glVersionMinor;
  glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
  glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);
  printf("\n=== OpenGL Implementation ===\n");
  printf("Vendor: %s\n", glGetString(GL_VENDOR));
  printf("GL Version: %s\n", glGetString(GL_VERSION));
  printf("GL Version (Strict): %d.%d\n", glVersionMajor, glVersionMinor);
  printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

  /* Windows Only
  GLenum error = glewInit();
  if (error != GLEW_OK) {
    fatalError("Could not initialize Glew!");
  }
   */

  // Make two windows so we draw on one buffer. This stops flickering.
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

  /*
  SDL_Event windowEvent;
  while (true) {
    if (SDL_PollEvent(&windowEvent)) {
      if (windowEvent.type == SDL_QUIT) break;
    }

    SDL_GL_SwapWindow(_window);
    if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
  }

  SDL_GL_DeleteContext(context);
  SDL_Quit();
   */

  initShaders();
}

void MainGame::initShaders() {
  _colorProgram.compileShaders(
    "/Users/patrick.opie/Documents/github/game-engine/src/shaders/colorShading.vert",
    "/Users/patrick.opie/Documents/github/game-engine/src/shaders/colorShading.frag");
  _colorProgram.addAttribute("vertexPosition");
  _colorProgram.addAttribute("vertexColor");
  _colorProgram.linkShaders();

}

void MainGame::gameLoop() {
  // Run game until game state is changed to exit
  while (_gameState != GameState::EXIT) {
    processInput();
    _time += 0.01;
    drawGame();
  }

}

void MainGame::processInput() {
  SDL_Event evnt;

  while (SDL_PollEvent(&evnt)) { // Poll event if exists
    switch (evnt.type) {
      case SDL_QUIT: // Quit event
        _gameState = GameState::EXIT;
        break;
      case SDL_MOUSEMOTION: // Mouse Event
        std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
    }

  }
}

void MainGame::drawGame() {



  // Set the base depth to 1.0
  glClearDepth(1.0);

  // Clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _colorProgram.use();

  GLuint timeLocation = _colorProgram.getUniformLocation("time");
  glUniform1f(timeLocation, _time);
  // Draw Sprite
  _sprite.draw();

  _colorProgram.unuse();

  // Swap our buffer and draw everything to the screen
  SDL_GL_SwapWindow(_window);
}
