#include "Camera.h"  

// Constructeur de la cam�ra
// On initialise sa position, sa cible et son vecteur "up"
Camera::Camera(glm::vec3 position, glm::vec3 target) :
    m_position(position),                     // Position de d�part de la cam�ra
    m_target(target),                         // Point regard�
    m_upVector(glm::vec3(0.0f, 1.0f, 0.0f)),  // D�finit l'axe vertical (Y+)
    m_renderer(nullptr)                       // Pas encore li� � un renderer
{
    // Ici tu peux ajouter d�autres initialisations si n�cessaire
}

// Mise � jour de la cam�ra en fonction d�une entit�
void Camera::update(Entity* entity) {
    // On place la cam�ra � la position de l�entit�
    m_position = entity->getPosition();

    // Et on d�finit comme "target" ce que l�entit� regarde
    // (il faut que Entity ait une m�thode getTarget() qui renvoie un glm::vec3)
    m_target = entity->getTarget();
	m_direction = entity->getDirection();
}

// Calcul de la matrice de vue (utilis�e par OpenGL pour transformer la sc�ne
// du rep�re monde vers le rep�re cam�ra)
glm::mat4 Camera::getViewMatrix() {
    // Petit debug dans la console pour voir la position de la cam�ra
    std::cout << "Camera Position: ("
        << m_direction.x << ", "
        << m_direction.y << ", "
        << m_direction.z << ")\n";

    // glm::lookAt cr�e une matrice View en utilisant position, target et upVector
    return glm::lookAt(m_position, m_direction, m_upVector);
}
