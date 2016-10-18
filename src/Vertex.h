#ifndef GAME_ENGINE_VERTEX_H
#define GAME_ENGINE_VERTEX_H

// #include <gl/glew.h> use "OpenGL/gl3.h" instead for mac
#include <OpenGL/gl3.h>

struct Vertex {
  // Use case of compositions
  struct Position {
    float x;
    float y;
  } position;

  struct Color {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
  } color;
  // float position[2];
  // GLubyte color[4];
  // unsigned char color[3]; // 0 to 255
};

#endif //GAME_ENGINE_VERTEX_H
