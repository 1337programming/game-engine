#include "IOManager.h"

#include <fstream>

bool IOManager::readFileToBuffer(std::string filepath, std::vector<char> &buffer) {

  std::ifstream file(filepath, std::ios::binary);
  if (file.fail()) {
    perror(file.c_str());
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
}