#ifndef GAME_ENGINE_IOMANAGER_H
#define GAME_ENGINE_IOMANAGER_H

#include <vector>
#include <string>

namespace Engine {


  class IOManager {

    public:
      static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
  };

}
#endif //GAME_ENGINE_IOMANAGER_H
