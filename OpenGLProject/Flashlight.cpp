#pragma once

#include "Flashlight.h"

void Flashlight::onPress() {
	if (!m_isPressed) {
		m_isPressed = true;
	}
}
void Flashlight::onRelease() {
	if (m_isPressed) {
		m_isPressed = false;
		m_player->processFlashLightKey();
	}
}
void Flashlight::ifPressed() {
	if (m_isPressed) {
		// Rien
	}
}