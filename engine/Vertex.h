#ifndef GAME_ENGINE_VERTEX_H
#define GAME_ENGINE_VERTEX_H

// #include <gl/glew.h> use "OpenGL/gl3.h" instead for mac
#include <OpenGL/gl3.h>
#include "Position.h"
#include "Color.h"
#include "UV.h"

struct Vertex {

  // Relative position X, Y
  Position position;

  // R, G, B, A
  Color color;

  // UV Texture coordinates
  UV uv;

  void setPosition(float x, float y) {
    position.x = x;
    position.y = y;
  }

  void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
  }

  void setUV(float u, float v) {
    uv.u = u;
    uv.v = v;
  }

};

#endif //GAME_ENGINE_VERTEX_H
