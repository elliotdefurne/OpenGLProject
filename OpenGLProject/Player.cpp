#include "Player.h"

/**
 * @brief Met à jour la logique du joueur
 *
 * Pour l'instant, cette fonction est vide.
 * Elle pourra gérer les animations, collisions, ou autres mises à jour futures.
 */
void Player::update()
{
}

/**
 * @brief Dessine le joueur à l'écran
 *
 * Actuellement vide. On pourra y ajouter le rendu du joueur ou ses effets graphiques.
 */
void Player::draw()
{
}

/**
 * @brief Traite les touches de direction et déplace le joueur
 *
 * @param direction Constante indiquant la direction du mouvement
 *
 * Déplace le joueur selon la direction passée en paramètre et en tenant
 * compte de la vitesse et du deltaTime pour un mouvement fluide.
 */
void Player::proccessDirectionKey(int direction) {
    // Vitesse de déplacement du joueur
    float velocity = Constants::PLAYER_SPEED * m_renderer->getDeltaTime();

    if (direction == direction::FORWARD)
        m_position += glm::vec3(0.0f, 0.0f, 1.0f) * velocity;
    if (direction == direction::BACKWARD)
        m_position += glm::vec3(0.0f, 0.0f, -1.0f) * velocity;
    if (direction == direction::LEFT)
        m_position += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
    if (direction == direction::RIGHT)
        m_position += glm::vec3(-1.0f, 0.0f, 0.0f) * velocity;
    if (direction == direction::UP)
        m_position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
    if (direction == direction::DOWN)
        m_position += glm::vec3(0.0f, -1.0f, 0.0f) * velocity;
}
