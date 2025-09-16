#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "Renderer.h"

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target);
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(int direction);
	//void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	glm::vec3 Position;
	float m_Front = 2.0f;
	float m_Right = 1.0f;
	// Caméra par défaut : positionnée en diagonale pour une vue 3D claire
	glm::vec3 m_cameraPos = glm::vec3(3.0f, 3.0f, 3.0f);      // Position de la caméra
	glm::vec3 m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);   // Point regardé
	glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);       // Direction "haut" de la caméra
private:
	Renderer* m_renderer;
};



