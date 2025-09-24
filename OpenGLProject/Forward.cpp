#pragma once

#include "Forward.h"

void Forward::onPress() {
	if (!m_isPressed) {
		m_isPressed = true;
	}
}
void Forward::onRelease() {
	if (m_isPressed) {
		m_isPressed = false;
	}
}
void Forward::ifPressed() {
	if (m_isPressed) {
		m_player->proccessDirectionKey(direction::FORWARD);
	}
}