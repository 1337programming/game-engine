#include "Engine.h"

#include <SDL.h>
#include <OpenGL/gl3.h>

namespace Engine {

  int init() {
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Tell SDL that we want a double buffered window so we don't get flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Set GL versions
    // @TODO review, this should be handled by client
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    return 0;
  }

}