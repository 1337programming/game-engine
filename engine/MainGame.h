#ifndef GAME_ENGINE_MAINGAME_H
#define GAME_ENGINE_MAINGAME_H

#include "Engine.h"
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include "Window.h"
#include <vector>

// This class for initial testing of the engine
// Eventually we will use the JS scripts to run this
enum class GameState {
    PLAY, EXIT
};


class MainGame {

  public:

    MainGame();

    ~MainGame();

    void run();

  private:
    void initSystems();

    void initShaders();

    void gameLoop();

    void processInput();

    void drawGame();

    void calculateFPS();

    Engine::Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    std::vector<Engine::Sprite *> _sprites;

    Engine::GLSLProgram _colorProgram;

    float _fps;
    float _frameTime;
    float _maxFPS;
    float _time;

};


#endif //GAME_ENGINE_MAINGAME_H
