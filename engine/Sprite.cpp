#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace Engine {


  Sprite::Sprite() {
    _vboID = 0; // Always set vertex buffer objects to 0

  }

  Sprite::~Sprite() {
    if (_vboID != 0) {
      glDeleteBuffers(1, &_vboID);
    }

  }

  void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    _texture = ResourceManager::getTexture(texturePath);

    // Generate Buffer
    if (_vboID == 0) { // Ensure it is not already generated
      glGenBuffers(1, &_vboID);
    }

    Vertex vertexData[6];

    // First Triangle
    vertexData[0].setPosition(x + width, y + height);
    vertexData[0].setUV(1.0f, 1.0f);

    vertexData[1].setPosition(x, y + height);
    vertexData[1].setUV(0.0f, 1.0f);

    vertexData[2].setPosition(x, y);
    vertexData[2].setUV(0.0f, 0.0f);

    // Second Triangle
    vertexData[3].setPosition(x, y);
    vertexData[3].setUV(0.0f, 0.0f);

    vertexData[4].setPosition(x + width, y);
    vertexData[4].setUV(1.0f, 0.0f);

    vertexData[5].setPosition(x + width, y + height);
    vertexData[5].setUV(1.0f, 1.0f);

    // Set all vertex colors to magenta
    for (int i = 0; i < 6; i++) {
      vertexData[i].setColor(255, 0, 255, 255);
    }

    vertexData[1].setColor(0, 0, 255, 255);

    vertexData[4].setColor(0, 255, 0, 255);

    // Tell opengl to bind our vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    // Upload the data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    //Unbind the Buffer (Optional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void Sprite::draw() {

    glBindTexture(GL_TEXTURE_2D, _texture.id);

    // Bind the buffer object
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);



    // Disable the vertex attrib array. This is not optional
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

}