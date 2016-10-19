#ifndef GAME_ENGINE_IOMANAGER_H
#define GAME_ENGINE_IOMANAGER_H

#include <vector>

class IOManager {

  public:
    static bool readFileToBuffer(std::string filepath, std::vector<char>& buffer);
};
#endif //GAME_ENGINE_IOMANAGER_H
