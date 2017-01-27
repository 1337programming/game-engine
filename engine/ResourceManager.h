#ifndef GAME_ENGINE_RESOURCEMANAGER_H
#define GAME_ENGINE_RESOURCEMANAGER_H

#include "TextureCache.h"
#include "GLTexture.h"
#include <string>

namespace Engine {

  class ResourceManager {

    public:
      static GLTexture getTexture(std::string texturePath);

    private:
      static TextureCache _textureCache;
  };

}


#endif //GAME_ENGINE_RESOURCEMANAGER_H
