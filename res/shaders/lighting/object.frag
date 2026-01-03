#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;

const vec3 objColor = vec3(1.0, 0.5, 0.31);

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
  // Ambient
  vec3 ambient = 0.1 * lightColor;
  // Diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;
  // Specular
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = 0.5 * spec * lightColor;
  FragColor = vec4((ambient + diffuse + specular) * objColor, 1.0f);
}
