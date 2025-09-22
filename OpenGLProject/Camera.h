#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

#include "Renderer.h"
#include "Entity.h"

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 getViewMatrix();
	void update(Entity* entity);
private:
	Renderer* m_renderer;
	glm::vec3 m_position = glm::vec3(3.0f, 3.0f, 3.0f);			// Position de la caméra
	glm::vec3 m_target = glm::vec3(0.0f, 0.0f, 0.0f);			// Point regardé
	glm::vec3 m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);			// Direction "haut" de la caméra
};



