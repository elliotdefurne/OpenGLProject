#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

#include "Renderer.h"
#include "Entity.h"
#include "Direction.h"

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(3.0f, 3.0f, 3.0f), Direction* direction = new Direction(-90.0f, 0.0f));

	// Retourne la matrice "View" (vue cam�ra) calcul�e via glm::lookAt
	glm::mat4 getViewMatrix();

	// Met � jour la cam�ra en fonction d�une entit� (ex : suivre un joueur)
	void update(Entity* entity);
private:
	Renderer* m_renderer;
	Direction* m_direction;

	glm::vec3 m_position = glm::vec3(3.0f, 3.0f, 3.0f);			// Position de la cam�ra
	glm::vec3 m_front = glm::vec3(1.0f, 1.0f, 0.0f);			// Point regard�
	glm::vec3 m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);			// Direction "haut" de la cam�ra


};



