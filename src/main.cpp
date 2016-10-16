#include <iostream>
#include <SDL.h>
#include "SDL_opengl.h"
#include "MainGame.h"
#ifdef _WIN32
  #include <Windows.h>
  #include <GL/glew.h>
#elif __APPLE__
#elif __linux__
#endif

int main(int argc, char** argv) {

  MainGame mainGame;
  mainGame.run();

  return 0;
}