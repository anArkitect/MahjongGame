#version 400

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform samplerCube cubemap; 
uniform vec3 eyePos;


void main()
{
  //FragColor = 0.8 * vec4(0.54, 0.17, 0.89, 1.0);
  vec3 eyeDir = normalize(eyePos - FragPos);
  vec3 refDir = reflect(eyeDir, normalize(Normal));


  FragColor = vec4(texture(cubemap, refDir).rgb, 1.0);
}