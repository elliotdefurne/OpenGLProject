#include "LightSource.h"

#include "Vertex.h"   // Structure d'un sommet (position, couleur, texture…)
#include "Mesh.h"     // Classe pour gerer les buffers OpenGL et dessiner
#include "Shader.h"   // Classe pour les shaders OpenGL
#include "Texture.h"  // Classe pour les textures
#include "Transformation.h" // Classe pour position, rotation et scale
#include "Cube.h"

LightSource::LightSource(glm::vec3 center, Shader* shader, Texture* texture, glm::vec3 lightColor) : m_lightColor(lightColor) {
	m_cube = std::make_unique<Cube>(center, 0.5f, shader, texture, this);
	m_ambient = glm::vec3(0.25f, 0.25f, 0.25f);
	m_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

LightSource::~LightSource() {
	
}

void LightSource::draw() {
	m_cube->draw();
}

void LightSource::update() {
	// Pour l'instant, la source de lumière ne fait rien de spécial
}

std::unique_ptr<Cube>& LightSource::getCube() { return m_cube; }
glm::vec3 LightSource::getLightColor() { return m_lightColor; }
glm::vec3 LightSource::getAmbient() { return m_ambient; }
glm::vec3 LightSource::getDiffuse() { return m_diffuse; }
glm::vec3 LightSource::getSpecular() { return m_specular; }
glm::vec3 LightSource::getPos() { return m_cube->getCenter(); }