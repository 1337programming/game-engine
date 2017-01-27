//
// Created by Opie, Patrick on 1/26/17.
//

#include "Window.h"
#include "Errors.h"

namespace Engine {

  Window::~Window() {

  }

  Window::Window() {

  }

  int Window::create(std::string windowName, int screenWidth, int screenHeight, int currentFlags) {


    Uint32 flags = SDL_WINDOW_OPENGL;

    if (currentFlags & INVISIBLE) {
      flags |= SDL_WINDOW_HIDDEN;
    }
    if (currentFlags & FULLSCREEN) {
      flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    if (currentFlags & BORDERLESS) {
      flags |= SDL_WINDOW_BORDERLESS;
    }

    // Open an SDL Window
    _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth,
                                  screenHeight,
                                  flags);

    if (_sdlWindow == nullptr) {
      fatalError("SDL Window could not be created!");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
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

    return 0;
  }

  void Window::swapBuffer() {
    SDL_GL_SwapWindow(_sdlWindow);
  }

  int Window::getScreenWidth() {
    return _screenWidth;
  }

  int Window::getScreenHeight() {
    return _screenHeight;
  }

}