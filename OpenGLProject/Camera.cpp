#include "Camera.h"  

// Constructeur de la caméra
// On initialise sa position, sa cible et son vecteur "up"
Camera::Camera(glm::vec3 position, glm::vec3 target) :
    m_position(position),                     // Position de départ de la caméra
    m_target(target),                         // Point regardé
    m_upVector(glm::vec3(0.0f, 1.0f, 0.0f)),  // Définit l'axe vertical (Y+)
    m_renderer(nullptr)                       // Pas encore lié à un renderer
{
    // Ici tu peux ajouter d’autres initialisations si nécessaire
}

// Mise à jour de la caméra en fonction d’une entité
void Camera::update(Entity* entity) {
    // On place la caméra à la position de l’entité
    m_position = entity->getPosition();

    // Et on définit comme "target" ce que l’entité regarde
    // (il faut que Entity ait une méthode getTarget() qui renvoie un glm::vec3)
    m_target = entity->getTarget();
	m_direction = entity->getDirection();
}

// Calcul de la matrice de vue (utilisée par OpenGL pour transformer la scène
// du repère monde vers le repère caméra)
glm::mat4 Camera::getViewMatrix() {
    // Petit debug dans la console pour voir la position de la caméra
    std::cout << "Camera Position: ("
        << m_direction.x << ", "
        << m_direction.y << ", "
        << m_direction.z << ")\n";

    // glm::lookAt crée une matrice View en utilisant position, target et upVector
    return glm::lookAt(m_position, m_direction, m_upVector);
}
