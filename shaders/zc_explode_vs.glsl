#version 400
in vec3 aPos;
in vec2 aTexCoords;
in vec3 aNormal;


uniform mat4 PVM;
uniform mat4 M;
uniform mat4 V;
uniform mat4 transInverModel;
uniform vec3 midPoint;
uniform float time;

out VS_OUT {
    vec3 FragPos;
    vec2 texCoords;
    vec3 Normal;
    
} vs_out;



void main()
{
  vs_out.texCoords = aTexCoords;

  vec3 temp;
  temp.x = aPos.x;
  temp.y = aPos.y + 0.015 * sin(aPos.x * 10 + time * 5);
  temp.z = aPos.z;

  gl_Position = PVM * vec4(temp, 1.0);

  vs_out.Normal = vec3(M*vec4(aNormal, 0.0f));

  vs_out.FragPos = vec3(M*vec4(aPos, 1.0));
}