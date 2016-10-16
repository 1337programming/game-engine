#ifndef GAME_ENGINE_MAINGAME_H
#define GAME_ENGINE_MAINGAME_H

#pragma once
#include <SDL.h>
#include <SDL_opengl.h>

enum class GameState {PLAY, EXIT};


class MainGame {

  public:

    MainGame();

    ~MainGame();

    void run();



  private:
    void initSystems();
    void gameLoop();
    void processInput();
    void drawGame();
    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

};


#endif //GAME_ENGINE_MAINGAME_H
