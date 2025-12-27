#version 330 core
out vec4 FragColor;
in vec3 pos;

void main() {
  float ambientStrenth = 1.0;
  //vec3 objColor = ambientStrenth * vec3(1.0, 0.5, 0.31);
  vec3 objColor = ambientStrenth * pos;
  FragColor = vec4(objColor, 1.0f);
}
