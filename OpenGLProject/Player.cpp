#include "Player.h"

void Player::update()
{
}
void Player::draw()
{
}

void Player::proccessDirectionKey(int direction) {
	float velocity = Constants::PLAYER_SPEED * m_renderer->getDeltaTime(); // Vitesse de déplacement du joueur
	if (direction == direction::FORWARD)
		m_position += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
	if (direction == direction::BACKWARD)
		m_position += glm::vec3(-1.0f, 0.0f, 0.0f) * velocity;
	if (direction == direction::LEFT)
		m_position += glm::vec3(0.0f, 0.0f, 1.0f) * velocity;
	if (direction == direction::RIGHT)
		m_position += glm::vec3(0.0f, 0.0f, -1.0f) * velocity;
	if (direction == direction::UP)
		m_position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
	if (direction == direction::DOWN)
		m_position += glm::vec3(0.0f, -1.0f, 0.0f) * velocity;
}