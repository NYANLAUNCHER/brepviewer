#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
private:
  GLint m_ID;
  GLenum m_target;
  int m_nrChannels;
  int m_width;
  int m_height;
public:
  Texture(GLenum target, std::string filepath, bool flipY);
  void activate(GLenum unit) const;
}
