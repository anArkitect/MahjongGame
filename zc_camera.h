#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**************************************
 * Default values
 */
const float CAMERA_YAW = 0.0f;
const float CAMERA_PITCH = 0.0f;
const float CAMERA_MOVE_SPEED = 50.0f;
const float CAMERA_ROTATE_SPEED = 0.1f;
const float CAMERA_FOV = 80.0f;


enum Camera_Movement
{
	CAMERA_FORWARD,
	CAMERA_BACKWARD,
	CAMERA_LEFT,
	CAMERA_RIGHT,
};



class Camera
{
public:
	/**********************************
	 * member variables: 10 = 5 + 2 +3
	 * 位置 + 3个坐标轴 + 世界坐标系的y轴
	 * 2个角度
	 * 2个速度 +　摄像机视角
	 */
	glm::vec3 cam_pos;
	glm::vec3 cam_forward;
	glm::vec3 cam_right;
	glm::vec3 cam_up;
	glm::vec3 world_up;

	float cam_yaw;
	float cam_pitch;

	float cam_moveSpeed;
	float cam_rotateSpeed;
	float cam_zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = CAMERA_YAW, float pitch = CAMERA_PITCH) :
		cam_forward(glm::vec3(0.0f, 0.0f, -1.0f)),
		cam_moveSpeed(CAMERA_MOVE_SPEED),
		cam_rotateSpeed(CAMERA_ROTATE_SPEED),
		cam_zoom(CAMERA_FOV)
	{
		cam_pos = position;
		world_up = up;
		cam_yaw = yaw;
		cam_pitch = pitch;
	}



	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
		cam_forward(glm::vec3(0.0f, 0.0f, -1.0f)),
		cam_moveSpeed(CAMERA_MOVE_SPEED),
		cam_rotateSpeed(CAMERA_ROTATE_SPEED),
		cam_zoom(CAMERA_FOV)
	{
		cam_pos = glm::vec3(posX, posY, posZ);
		world_up = glm::vec3(upX, upY, upZ);
		cam_yaw = yaw;
		cam_pitch = pitch;
		updateCameraVectors();
	}


	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(cam_pos, cam_pos + cam_forward, cam_up);
	}


	void processKeyboard(Camera_Movement cam_direction, float deltaTime)
	{
		float velocity = cam_moveSpeed * deltaTime;
		if (cam_direction == CAMERA_FORWARD)	cam_pos += cam_forward * velocity;
		if (cam_direction == CAMERA_BACKWARD)	cam_pos -= cam_forward * velocity;
		if (cam_direction == CAMERA_LEFT)		cam_pos -= cam_right * velocity;
		if (cam_direction == CAMERA_RIGHT)		cam_pos += cam_right * velocity;
	}



	void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= CAMERA_ROTATE_SPEED;
		yOffset *= CAMERA_ROTATE_SPEED;

		cam_yaw += xOffset;
		cam_pitch += yOffset;

		if (constrainPitch)
		{
			if (cam_pitch > 89.0f)	cam_pitch = 89.0f;
			if (cam_pitch < -89.0f)	cam_pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void processWheelScroll(float direction)
	{
		cam_pos.x += direction * cam_forward.x;
		cam_pos.y += direction * cam_forward.y;
		cam_pos.z += direction * cam_forward.z;

		updateCameraVectors();
	}

private:
	/******************************************
	* change the forward, up and right vectors
	*/
	void updateCameraVectors()
	{
		glm::vec3 front;

		front.x = cos(glm::radians(cam_pitch)) * sin(glm::radians(cam_yaw));
		front.y = sin(glm::radians(cam_pitch));
		front.z = cos(glm::radians(cam_pitch)) * cos(glm::radians(cam_yaw)) * (-1);
		cam_forward = glm::normalize(front);

		cam_right = glm::normalize(glm::cross(cam_forward, world_up));
		cam_up = glm::normalize(glm::cross(cam_right, cam_forward));
	}


};