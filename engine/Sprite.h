#include <OpenGL/gl3.h>

#ifndef GAME_ENGINE_SPRITE_H
#define GAME_ENGINE_SPRITE_H


class Sprite {

  public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float width, float height);

    void draw();

  private:
    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboID; // GLuint is same as unsigned int except its guaranteed to be 32-bit

};


#endif //GAME_ENGINE_SPRITE_H
