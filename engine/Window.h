#ifndef GAME_ENGINE_WINDOW_H
#define GAME_ENGINE_WINDOW_H

#include <string>
#include <SDL.h>
#include <OpenGL/gl3.h>

namespace Engine {

  enum WindowFlags {
    INVISIBLE = 0x1,
    FULLSCREEN = 0x2,
    BORDERLESS = 0x4
  };

  class Window {

    public:

      Window();

      ~Window();

      int create(std::string windowName, int screenWidth, int screenHeight, int currentFlags);

      int getScreenWidth();

      int getScreenHeight();

      void swapBuffer();

    private:
      SDL_Window *_sdlWindow;
      int _screenWidth;
      int _screenHeight;


  };

}
#endif //GAME_ENGINE_WINDOW_H
