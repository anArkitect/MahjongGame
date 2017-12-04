#version 400 core

// special attributes
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

// get the 
in VS_OUT {
		vec2 texCoords;
} gs_in[];

out vec2 TexCoords;

uniform float startTime;
uniform float time;
uniform int explosionStatus;

vec3 direction = vec3(0.0f, 0.0f, 0.0f);

vec4 explode(vec4 position, vec3 normal)
{
		float magnitude = 2.0;
		direction = normal * (time - startTime) * magnitude;
		return position + vec4(direction, 0.0);
}

vec3 GetNormal()
{
		vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
		vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
		return normalize(cross(a, b));
}

void main() {
		vec3 normal = GetNormal();
		if (explosionStatus)
			gl_Position = explode(gl_in[0].gl_Position, normal);
		else
			gl_Position = gl_in[0].gl_Position;	
		TexCoords = gs_in[0].texCoords;
		if (length(direction) <= 1)
			EmitVertex();
		
		if (explosionStatus) 
			gl_Position = explode(gl_in[1].gl_Position, normal);
		else
			gl_Position = gl_in[1].gl_Position;	
		TexCoords = gs_in[1].texCoords;
		if (length(direction) <= 1)
			EmitVertex();

		if (explosionStatus) 
			gl_Position = explode(gl_in[2].gl_Position, normal);
		else
			gl_Position = gl_in[2].gl_Position;	
		TexCoords = gs_in[2].texCoords;
		if (length(direction) <= 1)
			EmitVertex();

		EndPrimitive();
}