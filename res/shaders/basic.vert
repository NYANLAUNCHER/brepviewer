#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 translate;

void main() {
  gl_Position = proj * model * view * vec4(aPos+translate, 1.0f);
}
