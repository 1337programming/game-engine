#include "Sprite.h"

Sprite::Sprite() {
  _vboID = 0; // Always set vertex buffer objects to 0

}

Sprite::~Sprite() {
  if (_vboID != 0) {
    glDeleteBuffers(1, &_vboID);
  }

}

void Sprite::init(float x, float y, float width, float height) {
  _x = x;
  _y = y;
  _width = width;
  _height = height;

  // Generate Buffer
  if (_vboID == 0) { // Ensure it is not already generated
    glGenBuffers(1, &_vboID);
  }

  float vertexData[12];

  // First Triangle
  vertexData[0] = x + width;
  vertexData[1] = y + height;

  vertexData[2] = x;
  vertexData[3] = y + height;

  vertexData[4] = x;
  vertexData[5] = y;

  // Second Triangle
  vertexData[6] = x;
  vertexData[7] = y;

  vertexData[8] = x + width;
  vertexData[9] = y;

  vertexData[10] = x + width;
  vertexData[11] = y + height;

  // Bind Buffer -- make it active and set type
  glBindBuffer(GL_ARRAY_BUFFER, _vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  //Unbind Buffer
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
  // Bind
  glBindBuffer(GL_ARRAY_BUFFER, _vboID);

  // Enable vertex array for id 0
  glEnableVertexAttribArray(0); // Only need 1 Vertex Array for position

  // Draw

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, 6);


  glDisableVertexAttribArray(0); // Disable Vertex Array

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}