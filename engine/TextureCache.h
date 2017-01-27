#ifndef GAME_ENGINE_TEXTURECACHE_H
#define GAME_ENGINE_TEXTURECACHE_H

#include <map>
#include <string>
#include "GLTexture.h"

namespace Engine {

  class TextureCache {

    public:
      TextureCache();

      ~TextureCache();

      GLTexture getTexture(std::string texturePath);

    private:
      std::map<std::string, Engine::GLTexture> _textureMap;

  };

}

#endif //GAME_ENGINE_TEXTURECACHE_H
