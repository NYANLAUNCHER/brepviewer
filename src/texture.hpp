#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
private:
    // Texture id
    GLuint m_ID;
    // Type of texture, i.e. GL_TEXTURE_2D
    GLenum m_target;
    // Number of channels in texture
    int m_nrChannels;
    int m_width;
    int m_height;
public:
    Texture(GLenum target, std::string filepath, bool flipY);
    void activate(GLenum unit) const;
};
