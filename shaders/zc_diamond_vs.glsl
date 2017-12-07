#version 400

in vec3 aPos;

uniform mat4 PVM;

void main()
{
	gl_Position = PVM * vec4(aPos, 1.0);
}