#ifndef GAME_ENGINE_IMAGELOADER_H
#define GAME_ENGINE_IMAGELOADER_H

#include <string>
#include "GLTexture.h"

class ImageLoader {

  public:
    static GLTexture loadPNG(std::string filePath);

};


#endif //GAME_ENGINE_IMAGELOADER_H
