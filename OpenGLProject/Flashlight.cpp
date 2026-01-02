#pragma once

#include "Flashlight.h"

void Flashlight::onPress(InputContext context) {
	if (!m_isPressed) {
		m_isPressed = true;
	}
}
void Flashlight::onRelease(InputContext context) {
	if (m_isPressed) {
		m_isPressed = false;
		m_player->processFlashLightKey();
	}
}
void Flashlight::ifPressed(InputContext context) {
	if (m_isPressed) {
		// Rien
	}
}