#ifndef GAME_ENGINE_MAINGAME_H
#define GAME_ENGINE_MAINGAME_H

#pragma once
#include "Sprite.h"
#include "GLSLProgram.h"
#include <SDL.h>
#include <OpenGL/gl3.h>

enum class GameState {PLAY, EXIT};


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
    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    Sprite _sprite;

    GLSLProgram _colorProgram;

    float _time;

};


#endif //GAME_ENGINE_MAINGAME_H
