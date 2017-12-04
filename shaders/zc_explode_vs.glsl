#version 400
in vec3 aPos;
in vec2 aTexCoords;
in vec3 aNormal;

uniform mat4 PVM;
uniform mat4 M;
uniform mat4 V;

out VS_OUT {
    vec2 texCoords;
} vs_out;

void main()
{
  vs_out.texCoords = aTexCoords;
  gl_Position = PVM * vec4(aPos, 1.0); 
}