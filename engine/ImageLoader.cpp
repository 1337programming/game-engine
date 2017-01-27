#include "ImageLoader.h"
#include "picopng.h"
#include "IOManager.h"
#include "Errors.h"
#include <vector>

namespace Engine {

  GLTexture ImageLoader::loadPNG(std::string filePath) {
    // Not great practice to make texture copies on the stack but GLTexture is only a few bytes
    GLTexture texture = {};

    std::vector<unsigned char> out;
    std::vector<unsigned char> in;

    unsigned long width, height;

    if (IOManager::readFileToBuffer(filePath, in) == false) {
      fatalError("Failed to load PNG file to buffer");
    }

    int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

    if (errorCode != 0) {
      fatalError("decodePNG failed with error: " + std::to_string(errorCode));
    }

    glGenTextures(1, &(texture.id));

    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    texture.width = width;
    texture.height = height;

    // Unbind Current Texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
  }

}