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
	// Constructeur avec position et cible par défaut (caméra placée à (3,3,3) regardant vers (0,0,0))
	Camera(glm::vec3 position = glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f));

	// Retourne la matrice "View" (vue caméra) calculée via glm::lookAt
	glm::mat4 getViewMatrix();

	// Met à jour la caméra en fonction d’une entité (ex : suivre un joueur)
	void update(Entity* entity);
private:
	Renderer* m_renderer;
	glm::vec3 m_position = glm::vec3(3.0f, 3.0f, 3.0f);			// Position de la caméra
	glm::vec3 m_target = glm::vec3(0.0f, 0.0f, 0.0f);			// Point regardé
	glm::vec3 m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);			// Direction "haut" de la caméra

	//glm::vec3 m_direction = glm::normalize(m_position - m_target);	// Vecteur direction de la caméra en fonction de la position et de la cible
	glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
};



