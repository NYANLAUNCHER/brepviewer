#pragma once
#include "GL/glew.h"
#include <string>
#include <unordered_map>

class Shader {
private:
    GLint m_ID;
    std::unordered_map<std::string, GLint> m_knownUniforms;
    void checkCompileErrors(unsigned int shader_id, std::string type);
public:
    ///@param base_name The name of the shader without file extention
    Shader(std::string base_path, std::string base_name);
    void use() const;
    GLint getUniform(std::string name);
    void setBool(std::string name, bool value);
    void setInt(std::string name, int value);
    void setFloat(std::string name, float value);
};
