#pragma once

#include "Forward.h"

void Forward::onPress(InputContext context) {
	if (!m_isPressed) {
		m_isPressed = true;
	}
}
void Forward::onRelease(InputContext context) {
	if (m_isPressed) {
		m_isPressed = false;
	}
}
void Forward::ifPressed(InputContext context) {
	if (m_isPressed) {
		m_player->processDirectionKey(direction::FORWARD);
	}
}