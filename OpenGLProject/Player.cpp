#include "Player.h"

void Player::update()
{
}

void Player::draw()
{
}

void Player::processDirectionKey(int direction) {
    // Vitesse de déplacement du joueur
    float velocity;

    if (m_isSprinting) {
        velocity = Constants::PLAYER_SPRINTING_SPEED * m_renderer->getDeltaTime();
	}
    else {
        velocity = Constants::PLAYER_WALKING_SPEED* m_renderer->getDeltaTime();
    }
    if (direction == EntityRelativeDirection::FORWARD)
        m_position += m_direction->getDirectionVector() * velocity;
    if (direction == EntityRelativeDirection::BACKWARD)
        m_position -= m_direction->getDirectionVector() * velocity;
    if (direction == EntityRelativeDirection::LEFT)
        m_position -= m_direction->rotateRight90KeepY() * velocity;
    if (direction == EntityRelativeDirection::RIGHT)
        m_position += m_direction->rotateRight90KeepY() * velocity;
    if (direction == EntityRelativeDirection::UP)
        m_position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
    if (direction == EntityRelativeDirection::DOWN)
        m_position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
}

void Player::processMouseMovements(double yaw, double pitch) {
	m_direction->addDelta(yaw, pitch);
}