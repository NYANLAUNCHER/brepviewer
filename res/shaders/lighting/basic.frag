#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture0;
uniform vec3 lightColor;

void main() {
  FragColor = mix(texture(texture0, TexCoord), vec4(lightColor, 1.0), 0.2);
}
