#include "Particles.h"



GLuint create_particles_vao()
{
   //Attributeless rendering
   GLuint vao;
   glGenVertexArrays(1, &vao);
   return vao;
}

void draw_particles_vao(GLuint vao)
{
   const int num_particles = 1000;
   glBindVertexArray(vao);
   glDrawArrays(GL_POINTS, 0, num_particles);
}