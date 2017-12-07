#ifndef __INITSHADER_H__
#define __INITSHADER_H__

#include <windows.h>
#include <GL/GL.h>

GLuint InitShader( const char* computeShaderFile);
GLuint InitShader( const char* vertexShaderFile, const char* fragmentShaderFile );
GLuint InitShader( const char* vertexShaderFile, const char* geometryShader, const char* fragmentShaderFile );



void setBool(GLuint shaderProgram, std::string vertexAttri, bool value);

void setInt(GLuint shaderProgram, std::string vertexAttri, int value);

void setFloat(GLuint shaderProgram, std::string vertexAttri, float value);

void setMat4(GLuint shaderProgram, std::string vertexAttri, glm::mat4 value);

void setVec3(GLuint shaderProgram, std::string vertexAttri, glm::vec3 value);

void setVec3(GLuint shaderProgram, std::string vertexAttri, float x, float y, float z);

void setVec4(GLuint shaderProgram, std::string vertexAttri, glm::vec4 value);

void setVec4(GLuint shaderProgram, std::string vertexAttri, float x, float y, float z, float w);
#endif