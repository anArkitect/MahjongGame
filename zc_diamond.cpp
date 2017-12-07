#include "zc_diamond.h"

GLuint createDiamondVAO()
{
	GLuint VAO, VBO, EBO;

	const float diamondVertices[] = {
		0.2,	0.0,	0.0,
		0.0,	0.0,	-0.2,
		-0.2,	0.0,	0.0,
		0.0,	0.0,	0.2,
		0.0,	0.5,	0.0,
		0.0,	-0.2,	0.0
	};

	const int diamondIndices[] = {
		0, 1, 4,
		0, 3, 4,
		2, 3, 4,
		2, 1, 4,
		0, 1, 5,
		0, 3, 5,
		2, 3, 5,
		2, 1, 5,
	};

	
	

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); 
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(diamondVertices), &diamondVertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(diamondIndices), &diamondIndices, GL_STATIC_DRAW);

	//get the current shader program
	GLint shader_program = -1;
	glGetIntegerv(GL_CURRENT_PROGRAM, &shader_program);

	//get a reference to an attrib variable name in a shader
	GLint pos_loc = glGetAttribLocation(shader_program, "aPos");

	glEnableVertexAttribArray(pos_loc); //enable this attribute

										//tell opengl how to get the attribute values out of the vbo (stride and offset)
	glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glBindVertexArray(0); //unbind the vao

	return VAO;
}

void drawDiamondVAO(GLuint VAO)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
}