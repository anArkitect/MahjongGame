#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>


enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};


class Game
{
public:
	GameState State;
	GLboolean Keys[1024];
	GLuint	  Width, Height;

	Game(GLuint width, GLuint height);
	~Game();

	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};