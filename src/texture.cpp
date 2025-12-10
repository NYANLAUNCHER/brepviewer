#include "texture.hpp"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "util.hpp"

Texture::Texture(GLenum target, std::string filepath, bool flipY) {
    glGenTextures(1, &m_ID);
    m_target = target;
    glBindTexture(m_target, m_ID);
    // texture parameters
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load texture
    stbi_set_flip_vertically_on_load(flipY);
    unsigned char *data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
    if (!data) {
        std::cout << RED("Failed to load texture: ") << BLUE(filepath) << '\n';
        return;
    }

    GLenum format = GL_RGB;
    if (m_nrChannels == 1)      format = GL_RED;
    else if (m_nrChannels == 3) format = GL_RGB;
    else if (m_nrChannels == 4) format = GL_RGBA;

    glTexImage2D(m_target, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(m_target);

    std::cout << GREEN("Loaded Texture: ") << BLUE(filepath) << std::endl;
    stbi_image_free(data);
}

void Texture::activate(GLenum unit) const {
    glActiveTexture(unit);
    glBindTexture(m_target, m_ID);
}
