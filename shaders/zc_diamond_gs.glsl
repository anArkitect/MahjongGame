#version 400 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
	vec3 FragPos;
} gs_in[];


out vec3 Normal;
out vec3 FragPos;

uniform mat4 transInverModel;

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return vec3(transInverModel * vec4(normalize(cross(a, b)), 0.0));
}

void main() {
	
	Normal = GetNormal();
	gl_Position = gl_in[0].gl_Position;
	FragPos = gs_in[0].FragPos;
	
	EmitVertex();

	Normal = GetNormal();
	gl_Position = gl_in[1].gl_Position;
	FragPos = gs_in[1].FragPos;
	EmitVertex();

	Normal = GetNormal();
	gl_Position = gl_in[2].gl_Position;
	FragPos = gs_in[2].FragPos;
	EmitVertex();

	EndPrimitive();
}