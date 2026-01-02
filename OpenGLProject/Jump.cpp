#pragma once

#include "Jump.h"

void Jump::onPress(InputContext context) {
	if (!m_isPressed) {
		m_isPressed = true;
	}
}
void Jump::onRelease(InputContext context) {
	if (m_isPressed) {
		m_isPressed = false;
	}
}
void Jump::ifPressed(InputContext context) {
	if (m_isPressed) {
		m_player->processDirectionKey(direction::UP);
	}
}