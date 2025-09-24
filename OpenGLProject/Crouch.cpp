#pragma once

#include "Crouch.h"

void Crouch::onPress() {
	if (!m_isPressed) {
		m_isPressed = true;
	}
}
void Crouch::onRelease() {
	if (m_isPressed) {
		m_isPressed = false;
	}
}
void Crouch::ifPressed() {
	if (m_isPressed) {
		m_player->proccessDirectionKey(direction::DOWN);
	}
}