#version 330 core
in vec2 TexCoord;
out vec4 FragColor;// ignored for now

uniform vec3 lightColor;

void main() {
  FragColor = vec4(lightColor, 1.0);
}
