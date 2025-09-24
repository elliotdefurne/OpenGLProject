#pragma once

#include "KeyManager.h"

void KeyManager::loadKeys() {
	m_keys["Forward"] = new Forward(m_player);
	m_keys["Backward"] = new Backward(m_player);
	m_keys["Left"] = new Left(m_player);
	m_keys["Right"] = new Right(m_player);
	m_keys["Crouch"] = new Crouch(m_player);
	m_keys["Jump"] = new Jump(m_player);
	m_keys["Sprint"] = new Sprint(m_player);
	m_keys["Escape"] = new Escape(m_game);
}

void KeyManager::update() {
	for (const auto& pair : m_keys) {
		Key* key = pair.second;
		int state = glfwGetKey(glfwGetCurrentContext(), key->getKey());
		bool wasPressed = key->getStatus();
		key->ifPressed();
		if (state == GLFW_PRESS) {
			key->onPress();
		}
		else if (state == GLFW_RELEASE) {
			key->onRelease();
		}
	}
}