#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include <windows.h>
#include <GL/glew.h>

GLuint create_particles_vao();
void draw_particles_vao(GLuint vao);

#endif