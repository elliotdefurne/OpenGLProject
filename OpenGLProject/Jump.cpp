#pragma once

#include "Jump.h"

void Jump::onPress() {
	if (!m_isPressed) {
		m_isPressed = true;
	}
}
void Jump::onRelease() {
	if (m_isPressed) {
		m_isPressed = false;
	}
}
void Jump::ifPressed() {
	if (m_isPressed) {
		m_player->processDirectionKey(direction::UP);
	}
}