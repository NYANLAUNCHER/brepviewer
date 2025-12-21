#version 330 core
in vec2 TexCoord;// ignored for now
out vec4 FragColor;

uniform vec3 lightColor;

const float borderSize=0.005;
const vec4 borderColor=vec4(0.0, 0.0, 0.0, 1.0);

void main() {
  FragColor = vec4(lightColor, 1.0);
  if (TexCoord.x >= (1.0-borderSize)) {
    FragColor = borderColor;
  }
  if (TexCoord.x <= (borderSize)) {
    FragColor = borderColor;
  }
  if (TexCoord.y >= (1.0-borderSize)) {
    FragColor = borderColor;
  }
  if (TexCoord.y <= (borderSize)) {
    FragColor = borderColor;
  }
}
