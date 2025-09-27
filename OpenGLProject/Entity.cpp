#include "Entity.h"
#include "Player.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Entity::Entity(Renderer* renderer)
	: m_position(glm::vec3(0.0f, 0.0f, 3.0f)),
	  m_direction(new Direction(-90.0f, 0.0f)),
	  m_renderer(renderer)
{
	// Initialisation des attributs du joueur si nécessaire

}

Entity::~Entity() {

}

void Entity::update()
{
	// Logique de mise à jour du joueur (mouvement, interactions, etc.)

}

void Entity::draw()
{
	// Logique de dessin du joueur (si nécessaire)

}