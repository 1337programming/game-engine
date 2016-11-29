#include "MainGame.h"
#include "Errors.h"
#include <iostream>
#include <string>


MainGame::MainGame() :
  _window(nullptr),
  _screenWidth(1024),
  _screenHeight(768),
  _gameState(GameState::PLAY),
  _maxFPS(60.0f),
  _time(0.0f) {

}

MainGame::~MainGame() {

}

void MainGame::run() {
  initSystems();

  std::string texPath = "/Users/patrick.opie/Documents/github/game-engine/engine/textures/jimmyJump_pack/PNG/CharacterRight_Standing.png";
  _sprites.push_back(new Sprite());
  _sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, texPath);
  _sprites.push_back(new Sprite());
  _sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, texPath);
  _sprites.push_back(new Sprite());
  _sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, texPath);

  gameLoop();
}

void MainGame::initSystems() {
  // Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  // Tell SDL that we want a double buffered window so we don't get flickering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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


  // Set the background color to blue
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

  // Set VSync
  SDL_GL_SetSwapInterval(0);

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
    "/Users/patrick.opie/Documents/github/game-engine/engine/shaders/colorShading.vert",
    "/Users/patrick.opie/Documents/github/game-engine/engine/shaders/colorShading.frag");
  _colorProgram.addAttribute("vertexPosition");
  _colorProgram.addAttribute("vertexColor");
  _colorProgram.addAttribute("vertexUV");
  _colorProgram.linkShaders();

}

void MainGame::gameLoop() {
  // Run game until game state is changed to exit
  while (_gameState != GameState::EXIT) {

    // Used for frame time measuring
    float startTicks = SDL_GetTicks();

    processInput();
    _time += 0.01;
    drawGame();
    calculateFPS();

    // Print only once every 10 frames
    static int frameCounter = 0;
    frameCounter++;
    if (frameCounter == 10) {
      std::cout << _fps << std::endl;
      frameCounter = 0;
    }

    float frameTicks = SDL_GetTicks() - startTicks;
    // Limit FPS to max FPS
    if (1000.0f / _maxFPS > frameTicks) {
      SDL_Delay(1000.0f / _maxFPS - frameTicks);
    }
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
        //std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
        break;
    }
  }
}

void MainGame::drawGame() {
  // Set the base depth to 1.0
  glClearDepth(1.0);

  // Clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Enable the shader
  _colorProgram.use();

  // We are using texture unit 0
  glActiveTexture(GL_TEXTURE0);

  // Get the uniform location
  GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
  // Tell shader that the texture is in texture unit 0
  glUniform1i(textureLocation, 0);

  // Set the constantly changing time variable
  GLuint timeLocation = _colorProgram.getUniformLocation("time");
  glUniform1f(timeLocation, _time);

  // Draw Sprite
  for (int i = 0; i < _sprites.size(); ++i) {
    _sprites[i]->draw();
  }

  // Unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);

  // Disable the shader
  _colorProgram.unuse();

  // Swap our buffer and draw everything to the screen
  SDL_GL_SwapWindow(_window);
}

void MainGame::calculateFPS() {
  static const int NUM_SAMPLES = 10;
  static float frameTimes[NUM_SAMPLES];
  static int currentFrame = 0;

  static float prevTicks = SDL_GetTicks();

  float currentTicks;
  currentTicks = SDL_GetTicks();

  _frameTime = currentTicks - prevTicks;
  frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

  prevTicks = currentTicks;

  int count;
  currentFrame++;

  if (currentFrame < NUM_SAMPLES) {
    count = currentFrame;
  } else {
    count = NUM_SAMPLES;
  }

  float frameTimeAverage = 0;
  for (int i = 0; i < count; i++) {
    frameTimeAverage += frameTimes[i];
  }

  frameTimeAverage /= count;

  if (frameTimeAverage > 0) {
    _fps = 1000.0f / frameTimeAverage;
  } else {
    _fps = 60.0f;
  }


}