#include "MainGame.h"
#include "Errors.h"
#include <iostream>
#include <string>

MainGame::MainGame() :
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
  _sprites.push_back(new Engine::Sprite());
  _sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, texPath);
  _sprites.push_back(new Engine::Sprite());
  _sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, texPath);
  _sprites.push_back(new Engine::Sprite());
  _sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, texPath);

  gameLoop();
}

void MainGame::initSystems() {

  Engine::init();

  _window.create("Game Engine", _screenWidth, _screenHeight, 0);

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
  _window.swapBuffer();
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

