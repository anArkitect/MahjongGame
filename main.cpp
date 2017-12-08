#include <windows.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <irrklang/irrKlang.h>

#include "InitShader.h"
#include "LoadMesh.h"
#include "LoadTexture.h"
#include "imgui_impl_glut.h"

#include "Quad.h"
#include "Cube.h"
#include "Particles.h"

#include "zc_debug.h"
#include "zc_glutInit.h"
#include "zc_moveControl.h"
#include "zc_resource_manager.h"
#include "zc_camera.h"
#include "zc_diamond.h"


const float SCR_WIDTH = 1200.0f;
const float SCR_HEIGHT = 800.0f;

static const std::string cube_name = "cubemap";
GLuint cubemap_id = -1; //Texture id for cubemap

// shader
float shininess = 32.0f;

// set the camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2 ;
bool isMouseFirstClick = true;

static bool cameraMoveEnabled = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;



//Quadrilateral
static const std::string quad_vs("./shaders/quad_vs.glsl");
static const std::string quad_fs("./shaders/quad_fs.glsl");
GLuint quad_shader_program = -1;
GLuint quad_vao = -1;
bool quad_enabled = false;

//Cube files and IDs
static const std::string cube_vs("./shaders/cube_vs.glsl");
static const std::string cube_fs("./shaders/cube_fs.glsl");
GLuint cube_shader_program = -1;
GLuint cube_vao = -1;
bool cube_enabled = true;

static const std::string particle_vs("./shaders/particle_vs.glsl");
static const std::string particle_fs("./shaders/particle_fs.glsl");
GLuint particle_shader_program = -1;
GLuint particle_vao = -1;
bool particles_enabled = false;

float camangle = 0.0f;
glm::vec3 campos(0.0f, 0.0f, 2.5f);
float aspect = 1.0f;


void draw_gui()
{
	// glUseProgram(tileShaderPrograms);
	static bool first_frame = true;
	ImGui_ImplGlut_NewFrame();
	static bool show_window = true;

	ImGui::Begin("Zhiwen Cao", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	//ImGui::SliderFloat("Shininess", &shininess, 10.0f, 50.0f);
	ImGui::Text("Press 'P' to Play / Pause the game");
	ImGui::Text("Press 'R' to Restart      the game");

	ImGui::Checkbox("Game Proceed", &game_enabled);

	if (game_enabled)
	{
		afterContinueTime = glutGet(GLUT_ELAPSED_TIME) * 0.001 - continuePointTime;
		if (isGameRestarted)
		{
			timeUsed = 0;
			afterContinueTime = 0;
			isGameRestarted = false;
			continuePointTime = glutGet(GLUT_ELAPSED_TIME) * 0.001;
		}
		ImGui::Text("Time Used: %d", timeUsed + afterContinueTime);
		

		pausePointTime = glutGet(GLUT_ELAPSED_TIME) * 0.001;
	}
	else
	{
		if (timeUsedAllowed)
		{
			timeUsed += afterContinueTime;
			timeUsedAllowed = false;
		}
		afterPauseTime = glutGet(GLUT_ELAPSED_TIME) * 0.001 - pausePointTime;
		ImGui::Text("Time Used: %d", timeUsed);
		continuePointTime = glutGet(GLUT_ELAPSED_TIME) * 0.001;
	}

	

	/*if (game_enabled)
	{
		durationTime = glutGet(GLUT_ELAPSED_TIME) * 0.001 - gameStartTime;
		timeUsedAllowed = true;
		ImGui::Text("Time Used: %d", timeUsed + durationTime);
	}
	else
	{
		gameStartTime = glutGet(GLUT_ELAPSED_TIME) * 0.001;
		if (timeUsedAllowed)
		{
			timeUsed += durationTime;
			timeUsedAllowed = false;
		}
		ImGui::Text("Time Used: %d", timeUsed);
		
	}*/

	/*
	static float slider = 0.0;

	if (ImGui::SliderFloat("Slider", &slider, 0.0f, +2.0f) || first_frame)
	{
		int slider_loc = glGetUniformLocation(tileShaderPrograms, "slider");
		if (slider_loc != -1)
		{
			glUniform1f(slider_loc, slider);
		}
	}

	static float alpha = 10.0f;
	if (ImGui::SliderFloat("Dullness", &alpha, 1.0f, 100.0f))
	{
		int alpha_loc = glGetUniformLocation(tileShaderPrograms, "alpha");
		if (alpha_loc != -1)
		{
			glUniform1f(alpha_loc, alpha);
		}
	}

	static float f = 0.0f;
	if (ImGui::SliderFloat("Wrap", &f, 0.0f, 1.0f))
	{
		int f_loc = glGetUniformLocation(tileShaderPrograms, "f");
		if (f_loc != -1)
		{
			glUniform1f(f_loc, f);
		}
	}

	static bool use_texture = true;
	if (ImGui::Checkbox("Use Texture", &use_texture))
	{
		int use_tex_loc = glGetUniformLocation(tileShaderPrograms, "use_texture");
		if (use_tex_loc != -1)
		{ 
			glUniform1i(use_tex_loc, use_texture);
		}
	}

	// glBindTexture(GL_TEXTURE_2D, textureIDs);

	const GLenum magnification_modes[2] = {GL_NEAREST, GL_LINEAR};
	const char* magnification_modes_labels[] = { "GL_NEAREST", "GL_LINEAR" };
	static int current_magnification_mode = 0;
	if(ImGui::Combo("Texture mag filter", &current_magnification_mode, magnification_modes_labels, 2))
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnification_modes[current_magnification_mode]);
	}
   
	const GLenum minification_modes[4] = { GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_LINEAR };
	const char* minfication_modes_labels[] = { "GL_NEAREST", "GL_LINEAR", "GL_NEAREST_MIPMAP_LINEAR", "GL_LINEAR_MIPMAP_LINEAR" };
	static int current_minification_mode = 0;
	if (ImGui::Combo("Texture min filter", &current_minification_mode, minfication_modes_labels, 4))
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minification_modes[current_minification_mode]);
	}
	*/
	ImGui::End();



	ImGui::Render();
	first_frame = false;
}



void draw_fish(const glm::mat4& P, const glm::mat4& V, float x, float y, float z, int tileOrder, bool explosionSatus)
{
	//float timeMS = glutGet(GLUT_ELAPSED_TIME);
	//float timeS = timeMS * 0.001;

   glm::mat4 T = glm::translate(glm::vec3(x, y, z));
   glm::mat4 S = glm::scale(glm::vec3(0.5f*tileData[tileOrder].mScaleFactor));
   glm::mat4 R = glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
   glm::mat4 M = T*S*R;
   glm::mat4 transInverModel = glm::transpose(glm::inverse(M));


   glUseProgram(tileShaderPrograms[tileOrder]);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, textureIDs[tileOrder]);
   setInt(tileShaderPrograms[tileOrder], "material.tex", 0);

   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
   setInt(tileShaderPrograms[tileOrder], "material.cubemap", 1);
   //setVec3(tileShaderPrograms[tileOrder], "midPoint", x + glm::sin(timeS) * 5, y, z + glm::cos(timeS) * 5);
   setMat4(tileShaderPrograms[tileOrder], "PVM", P*V*M);
   setMat4(tileShaderPrograms[tileOrder], "M", M);
   setMat4(tileShaderPrograms[tileOrder], "transInverModel", transInverModel);
   setMat4(tileShaderPrograms[tileOrder], "V", V);
   setBool(tileShaderPrograms[tileOrder], "explosionStatus", explosionSatus);
   setBool(tileShaderPrograms[tileOrder], "holdStatus", tileData[tileOrder].holdStatus);
   if (tileOrder == tileSelection)
		setBool(tileShaderPrograms[tileOrder], "hoverOver", true);
   else
	   setBool(tileShaderPrograms[tileOrder], "hoverOver", false);

   setFloat(tileShaderPrograms[tileOrder], "material.shininess", shininess);
   setVec3(tileShaderPrograms[tileOrder], "pointLights[0].position", glm::vec3(-1.5,  2.0, 0.0));
   setVec3(tileShaderPrograms[tileOrder], "pointLights[1].position", glm::vec3(-1.5, -2.0, 0.0));
   setVec3(tileShaderPrograms[tileOrder], "pointLights[2].position", glm::vec3( 3.3,  2.0, 0.0));
   setVec3(tileShaderPrograms[tileOrder], "pointLights[3].position", glm::vec3( 3.3, -2.0, 0.0));
   setVec3(tileShaderPrograms[tileOrder], "viewPos", camera.cam_pos);

   setVec3(tileShaderPrograms[tileOrder], "spotLight.position", x, y-0.5, z);
   setVec3(tileShaderPrograms[tileOrder], "spotLight.direction", glm::vec3(0.0, 1.0, 0.0));
   setVec3(tileShaderPrograms[tileOrder], "spotLight.ambientComponent", glm::vec3(0.1));
   setVec3(tileShaderPrograms[tileOrder], "spotLight.diffuseComponent", glm::vec3(0.54, 0.17, 0.89));
   setVec3(tileShaderPrograms[tileOrder], "spotLight.specularComponent", glm::vec3(1.0));
   setFloat(tileShaderPrograms[tileOrder], "spotLight.constantTermCoef", 1.0);
   setFloat(tileShaderPrograms[tileOrder], "spotLight.linearTermCoef", 0.09);
   setFloat(tileShaderPrograms[tileOrder], "spotLight.quadraticTermCoef", 0.032);
   setFloat(tileShaderPrograms[tileOrder], "spotLight.innerCutOff", glm::cos(glm::radians(25.0f)));
   setFloat(tileShaderPrograms[tileOrder], "spotLight.outerCutOff", glm::cos(glm::radians(50.0f)));
	

   glBindVertexArray(tileData[tileOrder].mVao);
   glDrawElements(GL_TRIANGLES, tileData[tileOrder].mNumIndices, GL_UNSIGNED_INT, 0);
}




void draw_quad(const glm::mat4& P, const glm::mat4& V)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

   glm::mat4 M, PVM;
   glm::vec4 color;
   glUseProgram(quad_shader_program);
   int PVM_loc = glGetUniformLocation(quad_shader_program, "PVM");
   int color_loc = glGetUniformLocation(quad_shader_program, "color");
   
   M = glm::translate(glm::vec3(0.0f, 0.0f, -1.0f));
   color = glm::vec4(1.0, 0.0, 0.0, 0.5);
   PVM = P*V*M;
   if (PVM_loc != -1)
   {
      glUniformMatrix4fv(PVM_loc, 1, false, glm::value_ptr(PVM));
   }
   if (color_loc != -1)
   {
      glUniform4fv(color_loc, 1, glm::value_ptr(color));
   }
   draw_quad_vao(quad_vao);


   M = glm::translate(glm::vec3(0.0f, 0.0f, +1.0f));
   color = glm::vec4(0.0, 0.0, 1.0, 0.5);
   PVM = P*V*M;
   if (PVM_loc != -1)
   {
      glUniformMatrix4fv(PVM_loc, 1, false, glm::value_ptr(PVM));
   }
   if (color_loc != -1)
   {
      glUniform4fv(color_loc, 1, glm::value_ptr(color));
   }
   draw_quad_vao(quad_vao);

   glDisable(GL_BLEND);
   glDepthMask(TRUE);

}


void draw_diamond(const glm::mat4& P, const glm::mat4& V, float x, float y, float z)
{
	glm::mat4 T = glm::translate(glm::vec3(x, y-0.3, z));
	glm::mat4 S = glm::scale(glm::vec3(0.3f));
	glm::mat4 M = T * S;
	glm::mat4 PVM = P * V * M;
	glm::mat4 transInverModel = glm::transpose(glm::inverse(M));

	glUseProgram(diamondShaderPrograms[tileSelection]);

	setMat4(diamondShaderPrograms[tileSelection], "PVM", PVM);
	setMat4(diamondShaderPrograms[tileSelection], "M", M);
	setMat4(diamondShaderPrograms[tileSelection], "transInverModel", transInverModel);
	setVec3(diamondShaderPrograms[tileSelection], "eyePos", camera.cam_pos);
	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
	setInt(diamondShaderPrograms[tileSelection], "cubemap", 0);

	drawDiamondVAO(diamondVAO);
}


void draw_cube(const glm::mat4& P, const glm::mat4& V)
{
   glUseProgram(cube_shader_program);
   int PVM_loc = glGetUniformLocation(cube_shader_program, "PVM");
   if (PVM_loc != -1)
   {
      glm::mat4 Msky = glm::scale(glm::vec3(50.0f));
      glm::mat4 PVM = P*V*Msky;
      PVM[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
      glUniformMatrix4fv(PVM_loc, 1, false, glm::value_ptr(PVM));
   }
   
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
   int cube_loc = glGetUniformLocation(cube_shader_program, "cubemap");
   if (cube_loc != -1)
   {
      glUniform1i(cube_loc, 1); // we bound our texture to texture unit 1
   }

   draw_cube_vao(cube_vao);
}



void draw_particles(const glm::mat4& P, const glm::mat4& V)
{

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glUseProgram(particle_shader_program);
	int PVM_loc = glGetUniformLocation(particle_shader_program, "PVM");
	if (PVM_loc != -1)
	{
		glm::mat4 PVM = P*V;
		glUniformMatrix4fv(PVM_loc, 1, false, glm::value_ptr(PVM));
	}

	draw_particles_vao(particle_vao);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}



// glut display callback function.
// This function gets called every time the scene gets redisplayed 
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the back buffer

	//glm::mat4 V = glm::lookAt(campos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))*glm::rotate(camangle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 V = camera.getViewMatrix();
	glm::mat4 P = glm::perspective(80.0f, aspect, 0.1f, 100.0f); //not affine

	// draw opaque objects first
	if (cube_enabled)
	{
		draw_cube(P, V);
	}


	if (quad_enabled)
	{
		draw_quad(P, V);
	}

	for (int i = 0; i < TILE_NR; i++)
		if (tileData[i].drawEnabled && game_enabled)
		{
			draw_fish(P, V, tilePos[i].x, tilePos[i].y, tilePos[i].z, i, tileData[i].explosionStatus);
		}

	for (int i = 0; i < TILE_NR; i++)
	{
		if (i == tileSelection && game_enabled)
		{
			draw_diamond(P, V, tilePos[i].x, tilePos[i].y, tilePos[i].z);
		}
	}
	

	if(particles_enabled)
	{
		draw_particles(P, V);
	}

	draw_gui();
	glutSwapBuffers();
}




void idle()
{

	float currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = 0.001 * (currentFrame - lastFrame);
	lastFrame = currentFrame;

	glutPostRedisplay();
   
	const int time_ms = glutGet(GLUT_ELAPSED_TIME);
	float time_sec = 0.001f*time_ms;
 
	for (int i = 0; i < TILE_NR; i++)
	{
		if (tileData[i].exploStartTimeAllowed)
		{
			tileData[i].exploStartTime = time_sec;
			
			debug(tileData[i].tileContent, tileData[i].exploStartTime);
		}

		tileData[i].exploStartTimeAllowed = false;

		glUseProgram(tileShaderPrograms[i]);

		int start_time_loc = glGetUniformLocation(tileShaderPrograms[i], "startTime");
		if (start_time_loc != -1)
		{
			//double check that you are using glUniform1f
			glUniform1f(start_time_loc, tileData[i].exploStartTime);
			
		}

		int time_loc = glGetUniformLocation(tileShaderPrograms[i], "time");
		if (time_loc != -1)
		{
			//double check that you are using glUniform1f
			glUniform1f(time_loc, time_sec);
		}

		glUseProgram(particle_shader_program);
		time_loc = glGetUniformLocation(particle_shader_program, "time");
		if (time_loc != -1)
		{
			//double check that you are using glUniform1f
			glUniform1f(time_loc, time_sec);
		}

		glUseProgram(diamondShaderPrograms[i]);
		setFloat(diamondShaderPrograms[i], "time", time_sec);
	}
}



void printGlInfo()
{
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


int myrandom(int i) { return std::rand() % i; }

void initOpenGl()
{
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SPRITE);       // allows textured points
	glEnable(GL_PROGRAM_POINT_SIZE); //allows us to set point size in vertex shader
	glClearColor(0.35f, 0.35f, 0.35f, 0.0f);

	// fishes


	srand(time(NULL));
	std::random_shuffle(tileNames.begin(), tileNames.end(), myrandom);


	for (int i = 0; i < TILE_NR; i++)
	{
		textureIDs[i] = LoadTexture(mesh_texture[tileNames[i]]);
		tileShaderPrograms[i] = InitShader(tile_vs_path.c_str(), tile_gs_path.c_str(), tile_fs_path.c_str());
		tileData[i] = LoadMesh(tileNames[i]);
	}



	// diamonds
	for (int i = 0; i < TILE_NR; i++)
	{
		diamondShaderPrograms[i] = InitShader(diamond_vs_path.c_str(), diamond_gs_path.c_str(), diamond_fs_path.c_str());
		//diamondShaderPrograms[i] = InitShader(diamond_vs_path.c_str(), diamond_fs_path.c_str());
		diamondVAO = createDiamondVAO();
	}
   
   
	// legacy: quad
	//quad_shader_program = InitShader(quad_vs.c_str(), quad_fs.c_str());
	//quad_vao = create_quad_vao();

	// cubemap
	cubemap_id = LoadCube(cube_name);

	cube_shader_program = InitShader(cube_vs.c_str(), cube_fs.c_str());
	cube_vao = create_cube_vao();

	// particle
	particle_shader_program = InitShader(particle_vs.c_str(), particle_fs.c_str());
	particle_vao = create_particles_vao();
}




// glut callbacks need to send keyboard and mouse events to imgui
void keyboard(unsigned char key, int x, int y)
{
	ImGui_ImplGlut_KeyCallback(key);

	float campSpeed = deltaTime * 2.0f;

	switch (key)
	{
		case ' ':
			selectTile();
			break;

		case 'w':
		case 'W':
			camera.processKeyboard(CAMERA_FORWARD, deltaTime);
			break;

		case 'a':
		case 'A':
			camera.processKeyboard(CAMERA_LEFT, deltaTime);
			break;

		case 's':
		case 'S':
			camera.processKeyboard(CAMERA_BACKWARD, deltaTime);
			break;

		case 'd':
		case 'D':
			camera.processKeyboard(CAMERA_RIGHT, deltaTime);
			break;

		case 'p':
		case 'P':
			if (game_enabled)
			{
				game_enabled = false;
				playSoundEffect("sounds/pauseSound.wav");
			}
			else
			{
				game_enabled = true;
				playSoundEffect("sounds/pauseSound.wav");
			}
				
			timeUsedAllowed = true;
			break;

		case 'r':
		case 'R':
			initOpenGl();
			isGameRestarted = true;
			playSoundEffect("sounds/startSound.wav");
			break;

		default:
			break;
	}
}

void keyboard_up(unsigned char key, int x, int y)
{
	ImGui_ImplGlut_KeyUpCallback(key);
}

void special_up(int key, int x, int y)
{
	ImGui_ImplGlut_SpecialUpCallback(key);
}

void passive(int x, int y)
{
	ImGui_ImplGlut_PassiveMouseMotionCallback(x, y);
}

void special(int key, int x, int y)
{
	ImGui_ImplGlut_SpecialCallback(key);

	switch (key)
	{
	case GLUT_KEY_UP:
		upMoveOnBoard();
		break;

	case GLUT_KEY_LEFT:
		leftMoveOnBoard();
		break;

	case GLUT_KEY_DOWN:
		downMoveOnBoard();
		break;

	case GLUT_KEY_RIGHT:
		rightMoveOnBoard();
		break;

	default:
		break;
	}
}

void passiveMotion(int x, int y)
{
	isMouseFirstClick = true;
}

void motion(int x, int y)
{
	ImGui_ImplGlut_MouseMotionCallback(x, y);

	if (isMouseFirstClick)
	{
		lastX = x;
		lastY = y;
		isMouseFirstClick = false;
	}

	float offsetX = x - lastX;
	float offsetY = lastY - y;
	lastX = x;
	lastY = y;

	camera.processMouseMovement(offsetX, offsetY);
}

void mouse(int button, int state, int x, int y)
{
	ImGui_ImplGlut_MouseButtonCallback(button, state);

}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	aspect = (float)w / h;
}

void mouse_wheel(int wheel, int direction, int x, int y)
{
	camera.processWheelScroll(direction);
	debug(direction);
	debug(camera.cam_pos.x, camera.cam_pos.y, camera.cam_pos.z);
}



int main(int argc, char **argv)
{
	int win = zcGlutInit(argc, argv, "MahjongProject");

	printGlInfo();

	//Register callback functions with glut. 
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialUpFunc(special_up);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passiveMotion);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMouseWheelFunc(mouse_wheel);


	playSoundEffect("sounds/backgroundSound.mp3", true);
	for (int i = 0; i < tileNames.size(); ++i)
	{
		mesh_texture[tileNames[i]] = textureNames[i];
	}

	initOpenGl();
	ImGui_ImplGlut_Init(); // initialize the imgui system

	//Enter the glut event loop.
	glutMainLoop();
	glutDestroyWindow(win);
	return 0;
}