#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragementShaderID(0) {
}

GLSLProgram::~GLSLProgram() {

}

void GLSLProgram::compileShaders(std::string &vertexShaderFilePath, std::string &fragmentShaderFilePath) {
  _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  if (_vertexShaderID == 0) {
    fatalError("Vertex shader failed to be created");
  }

  _fragementShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  if (_fragementShaderID == 0) {
    fatalError("Fragment shader failed to be created");
  }

  compileShader(vertexShaderFilePath, _vertexShaderID);

  compileShader(fragmentShaderFilePath, _fragementShaderID);

}

void GLSLProgram::linkShaders() {

}

void GLSLProgram::compileShader(const std::string &filePath, GLuint &id) {
  std::fstream vertexFile(filePath);
  if (vertexFile.fail()) {
    perror(filePath.c_str());
    fatalError("Failed to open " + filePath);
  }

  std::string fileContents = "";
  std::string line;

  while (std::getline(vertexFile, line)) {
    fileContents += line + "\n";
  }

  vertexFile.close();

  const char *contentsPrt = fileContents.c_str();
  glShaderSource(id, 1, &contentsPrt, nullptr);

  glCompileShader(id);

  GLint success = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

    // Provide the infolog in whatever manor you deem best.
    // Exit with failure.
    glDeleteShader(id); // Don't leak the shader.

    std::printf("%s\n", &errorLog[0]);
    fatalError("Shader " + filePath + " failed to compile");

  }
}
