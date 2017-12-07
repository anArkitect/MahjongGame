#version 400

out vec4 FragColor;

uniform samplerCube cubemap; 


void main()
{

  FragColor = 0.8 * vec4(0.54, 0.17, 0.89, 1.0);
}