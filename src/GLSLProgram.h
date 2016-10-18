#ifndef GAME_ENGINE_GLSLPROGRAM_H
#define GAME_ENGINE_GLSLPROGRAM_H

#include <string>
#include <OpenGL/gl3.h>


class GLSLProgram {

  public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

    void linkShaders();

    void addAttribute(const std::string& attributeName);

    void use();
    void unuse();

  private:

    int _numAttributes;

    void compileShader(const std::string& filePath, GLuint& id);
    GLuint _programID;

    GLuint _vertexShaderID;
    GLuint _fragementShaderID;



};

#endif //GAME_ENGINE_GLSLPROGRAM_H
