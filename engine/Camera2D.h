
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef GAME_ENGINE_CAMERA2D_H
#define GAME_ENGINE_CAMERA2D_H

namespace Engine {

  class Camera2D {

    public:
      Camera2D();

      ~Camera2D();

      void init(int screenWidth, int screenHeight);

      void update();

      // Setters
      void setPosition(glm::vec2& newPosition);

      void setScale(float newScale);

      // Getters
      glm::vec2 getPosition();

      float getScale();

      glm::mat4 getCameraMatrix();

    private:
      int _screenWidth;
      int _screenHeight;
      bool _needsMatrixUpdate;
      float _scale;
      glm::vec2 _position;
      glm::mat4 _cameraMatrix;
      glm::mat4 _orthoMatrix;


  };

}

#endif //GAME_ENGINE_CAMERA2D_H
