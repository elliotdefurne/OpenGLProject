#pragma once

#include "Crouch.h"

void Crouch::onPress(InputContext context) {
	if (!m_isPressed) {
		m_isPressed = true;
	}
}
void Crouch::onRelease(InputContext context) {
	if (m_isPressed) {
		m_isPressed = false;
	}
}
void Crouch::ifPressed(InputContext context) {
	if (m_isPressed) {
		m_player->processDirectionKey(direction::DOWN);
	}
}