#version 400
in vec3 aPos;
in vec2 aTexCoords;
in vec3 aNormal;


uniform mat4 PVM;
uniform mat4 M;
uniform mat4 V;
uniform mat4 transInverModel;

out VS_OUT {
    vec3 FragPos;
    vec2 texCoords;
    vec3 Normal;
    
} vs_out;



void main()
{
  vs_out.texCoords = aTexCoords;

  gl_Position = PVM * vec4(aPos, 1.0);

  vs_out.Normal = vec3(M*vec4(aNormal, 0.0f));

  vs_out.FragPos = vec3(M*vec4(aPos, 1.0));
}