#ifndef GAME_ENGINE_GLSLPROGRAM_H
#define GAME_ENGINE_GLSLPROGRAM_H

#include <string>
#include <OpenGL/gl3.h>


class GLSLProgram {

  public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders(std::string& vertexShaderFilePath, std::string& fragmentShaderFilePath);

    void linkShaders();

  private:

    void compileShader(const std::string& filePath, GLuint& id);
    GLuint _programID;

    GLuint _vertexShaderID;
    GLuint _fragementShaderID;



};

#endif //GAME_ENGINE_GLSLPROGRAM_H
