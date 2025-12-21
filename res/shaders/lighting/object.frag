#version 330 core
out vec4 FragColor;

void main() {
  float ambientStrenth = 0.1;
  vec3 objColor = ambientStrenth * vec3(1.0, 0.5, 0.31);
  FragColor = vec4(objColor, 1.0);
}
