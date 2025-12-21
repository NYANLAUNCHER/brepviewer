#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float scale;
//uniform vec3 translate;

void main() {
  TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
  //translate=vec3(1.0, 1.0, 1.0);
  gl_Position = proj * view * model * vec4(aPos*scale, 1.0);
}
