#ifndef GAME_ENGINE_VERTEX_H
#define GAME_ENGINE_VERTEX_H

// #include <gl/glew.h> use "OpenGL/gl3.h" instead for mac
#include <OpenGL/gl3.h>
#include "Position.h"
#include "Color.h"

struct Vertex {

  // Position X, Y
  Position position;

  // R, G, B, A
  Color color;

};

#endif //GAME_ENGINE_VERTEX_H
