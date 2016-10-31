#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

TextureCache::TextureCache() {

}

TextureCache::~TextureCache() {

}

GLTexture TextureCache::getTexture(std::string texturePath) {

  //std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);
  // Lookup texture in map
  auto mit = _textureMap.find(texturePath);

  // Check if it's not in the map
  if (mit == _textureMap.end()) {
    GLTexture newTexture = ImageLoader::loadPNG(texturePath);
    //std::pair<std::string, GLTexture> newPair(texturePath, newTexture); use make_pair() instead

    // Insert texture into the map
    _textureMap.insert(make_pair(texturePath, newTexture));

    std::cout << "Used Cached Texture!\n";

    return newTexture;
  }

  std::cout << "Loaded Texture!\n";

  return mit->second;
}