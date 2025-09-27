#include "Player.h"

void Player::update()
{
}

void Player::draw()
{
}

void Player::processDirectionKey(int direction) {
    // Vitesse de déplacement du joueur
    float velocity = Constants::PLAYER_SPEED * m_renderer->getDeltaTime();
    if (direction == direction::FORWARD)
        m_position += m_direction->getDirectionVector() * velocity;
    if (direction == direction::BACKWARD)
        m_position -= m_direction->getDirectionVector() * velocity;
    if (direction == direction::LEFT)
        m_position -= m_direction->rotateRight90KeepY() * velocity;
    if (direction == direction::RIGHT)
        m_position += m_direction->rotateRight90KeepY() * velocity;
    if (direction == direction::UP)
        m_position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
    if (direction == direction::DOWN)
        m_position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
}

void Player::processMouseMovements(double yaw, double pitch) {
	m_direction->addDelta(yaw, pitch);
}