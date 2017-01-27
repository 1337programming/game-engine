#ifndef GAME_ENGINE_GLTEXTURE_H
#define GAME_ENGINE_GLTEXTURE_H

#include <OpenGL/gl3.h>

namespace Engine {

  struct GLTexture {
    GLuint id;
    int width;
    int height;
  };

}
#endif //GAME_ENGINE_GLTEXTURE_H
