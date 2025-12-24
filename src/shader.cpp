#include "shader.hpp"
#include "util.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(std::string base_path, std::string base_name) {
    if (base_path.back() != '/') 
        base_path = base_path + "/";
    std::string vertPath = base_path + base_name + ".vert";
    std::string fragPath = base_path + base_name + ".frag";
    std::string vertSrc;
    std::string fragSrc;
    std::ifstream vertFile;
    std::ifstream fragFile;
    // ensure ifstream objects can throw exceptions:
    vertFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vertFile.open(vertPath);
        fragFile.open(fragPath);
        std::stringstream vertStream, fragStream;
        // read file's buffer contents into streams
        vertStream << vertFile.rdbuf();
        fragStream << fragFile.rdbuf();
        // close file handlers
        vertFile.close();
        fragFile.close();
        // convert stream into string
        vertSrc = vertStream.str();
        fragSrc = fragStream.str();
        std::cout << GREEN("Compiling vertex shader: ") << BLUE(vertPath) << "\n" <<
                     vertSrc << std::endl;
        std::cout << GREEN("Compiling fragment shader: ") << BLUE(fragPath) << "\n" <<
                     fragSrc << std::endl;
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vertSrc_cstr = vertSrc.c_str();
    const char* fragSrc_cstr = fragSrc.c_str();
    uint vertID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertID, 1, &vertSrc_cstr, NULL);
    glCompileShader(vertID);
    checkCompileErrors(vertID, "VERTEX");
    uint fragID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragID, 1, &fragSrc_cstr, NULL);
    glCompileShader(fragID);
    checkCompileErrors(fragID, "FRAGMENT");
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertID);
    glAttachShader(m_ID, fragID);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");
    glDeleteShader(vertID);
    glDeleteShader(fragID);
    // Init special uniforms
    this->model=glm::mat4(1.0f);
    this->view=glm::mat4(1.0f);
    this->proj=glm::mat4(1.0f);
}

void Shader::checkCompileErrors(unsigned int shader_id, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader_id, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_id, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}

void Shader::activate() const {
    glUseProgram(m_ID);
}

GLint Shader::getUniform(std::string name) {
    // Memoize uniform locations
    if (m_knownUniforms.find(name) != m_knownUniforms.end()) {
        return m_knownUniforms[name];
    } else {
        m_knownUniforms[name] = glGetUniformLocation(m_ID, name.c_str());
        return m_knownUniforms[name];
    }
    return -1;//fallback
}

void Shader::setBool(std::string name, bool value) {
    glUniform1i(getUniform(name.c_str()), (int)value);
}

void Shader::setInt(std::string name, int value) {
    glUniform1i(getUniform(name.c_str()), value);
}

void Shader::setFloat(std::string name, float value) {
    glUniform1f(getUniform(name.c_str()), value);
}

void Shader::setVec3f(std::string name, glm::vec3 value) {
    glUniform3fv(getUniform(name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4f(std::string name, glm::mat4& value) {
    glUniformMatrix4fv(getUniform(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
