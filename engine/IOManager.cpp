#include "IOManager.h"

#include <fstream>

namespace Engine {

  bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer) {

    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
      perror(filePath.c_str());
      return false;
    }

    // seek to the end
    file.seekg(0, std::ios::end);

    // get the file size
    int fileSize = file.tellg();

    // seek to the beginning
    file.seekg(0, std::ios::beg);

    // Reduce the file size by any header bytes that might be present
    fileSize -= file.tellg();

    buffer.resize(fileSize);
    file.read((char *) &(buffer[0]), fileSize);
    file.close();

    return true;
  }

}