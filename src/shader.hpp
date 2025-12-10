#pragma once
#include "GL/glew.h"
#include <string>

class Shader {
private:
  GLint m_ID;
public:
  ///@param base_name The name of the shader without file extention
  Shader(std::string base_path, std::string base_name);
  void use() const;
  void setInt(std::string name, int value);
  //void setVec();
  //void setMat();
};
