#version 400

in vec3 aPos;

out VS_OUT
{
	vec3 FragPos;
} vs_out;


uniform float time;
uniform mat4 PVM;
uniform mat4 M;


void main()
{
	gl_Position = PVM * vec4(aPos.x, aPos.y + sin(time * 2) * 0.3, aPos.z, 1.0) ;

	vs_out.FragPos = vec3(M*vec4(aPos, 1.0));
	//FragPos = vec3(M*vec4(aPos, 1.0));
}