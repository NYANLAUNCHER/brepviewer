#pragma once
#include "GL/glew.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
private:
    GLint m_ID;
    std::unordered_map<std::string, GLint> m_knownUniforms;
public:
    // Standalone utility function for checking shader compile errors
    static void checkCompileErrors(unsigned int shader_id, std::string type);
    ///@param base_name The name of the shader without file extention
    Shader(std::string base_path, std::string base_name);
    //Shader(const char* vert_src, const char* frag_src);
    void activate() const;
    inline GLint getID() const {return m_ID;}
    // update uniforms
    void update() const;
    GLint getUniform(std::string name);
    void setBool(std::string name, bool value);
    void setInt(std::string name, int value);
    void setFloat(std::string name, float value);
    void setVec3f(std::string name, glm::vec3 value);
    void setMat4f(std::string name, glm::mat4& value);
};
