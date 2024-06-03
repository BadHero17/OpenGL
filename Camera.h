#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum camera_movement {
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SENS = 0.1f;
const float SPEED = 2.0f;
const float FOV = 45.0f;

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Worldup;
	glm::vec3 Right;
	glm::vec3 Up;
	float Yaw;
	float Pitch;
	float Sens;
	float Speed;
	float Fov;
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :Front(glm::vec3(0.0f, 0.0f, -1.0f)), Speed(SPEED), Sens(SENS), Fov(FOV) {
		Position = position;
		Yaw = yaw;
		Pitch = pitch;
		Worldup = up;
		UpdateCameraVectors();
	}
	Camera(float xPos, float yPos, float zPos, float xUp, float yUp, float zUp, float yaw, float pitch) :Front(glm::vec3(0.0f, 0.0f, -1.0f)), Speed(SPEED), Sens(SENS), Fov(FOV) {
		Position = glm::vec3(xPos, yPos, zPos);
		Worldup = glm::vec3(xUp, yUp, zUp);
		Yaw = yaw;
		Pitch = pitch;
		UpdateCameraVectors();
	}
	glm::mat4 GetViewMatrix() {
		return glm::lookAt(Position, Position + Front, Up);
	}
	void ProcessKeyboard(camera_movement direction,float deltaTime) {
		float velocity = Speed * deltaTime;
		if (direction == FORWARD) {
			Position += velocity * Front;
		}
		if (direction == BACKWARD) {
			Position -= velocity * Front;
		}
		if (direction == RIGHT) {
			Position += velocity * Right;
		}
		if (direction == LEFT) {
			Position -= velocity * Right;
		}
		if (direction == UP) {
			Position += velocity * Up;
		}
		if (direction == DOWN) {
			Position -= velocity * Up;
		}
	}
	void ProcessMouseMovement(float xoffset,float yoffset,GLboolean constrainPitch=true) {
		xoffset *= Sens;
		yoffset *= Sens;
		Yaw -= xoffset;
		Pitch += yoffset;
		if (constrainPitch) {
			if (Pitch > 89.0f) {
				Pitch = 89.0f;
			}
			if (Pitch < -89.0f) {
				Pitch = -89.0f;
			}
		}
		UpdateCameraVectors();
	}
	void ProcessMouseScroll(float yoffset) {
		Fov += (float)yoffset;
		if (Fov > 45.0f) {
			Fov = 45.0f;
		}
		if (Fov < 1.0f) {
			Fov = 1.0f;
		}
	}
private:
	void UpdateCameraVectors() {
		glm::vec3 front = glm::vec3((float)cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)), (float)sin(glm::radians(Pitch)), (float)sin(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, Worldup));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};