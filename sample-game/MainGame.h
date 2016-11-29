#ifndef GAME_ENGINE_MAINGAME_H
#define GAME_ENGINE_MAINGAME_H

#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <vector>
#include <SDL.h>
#include <OpenGL/gl3.h>

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

    SDL_Window *_window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    std::vector<Sprite *> _sprites;

    GLSLProgram _colorProgram;

    float _fps;
    float _frameTime;
    float _maxFPS;
    float _time;

};


#endif //GAME_ENGINE_MAINGAME_H
