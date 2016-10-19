#ifndef GAME_ENGINE_IMAGELOADER_H
#define GAME_ENGINE_IMAGELOADER_H

#include "GLTexture.h"
#include <string>

class ImageLoader {

  public:
    static GLTexture loadPNG(std::string filePath);

};


#endif //GAME_ENGINE_IMAGELOADER_H
