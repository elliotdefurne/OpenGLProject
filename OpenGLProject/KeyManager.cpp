#pragma once

#include "KeyManager.h"
#include "Game.h"


Key* KeyManager::getKey(const std::string& name) {
	auto it = m_keys.find(name);
	if (it != m_keys.end()) {
		return it->second;
	}
	throw std::out_of_range("Key not found: " + name);
}

void KeyManager::loadKeys() {
	m_keys["Forward"] = new Forward(m_player);
	m_keys["Backward"] = new Backward(m_player);
	m_keys["Left"] = new Left(m_player);
	m_keys["Right"] = new Right(m_player);
	m_keys["Crouch"] = new Crouch(m_player);
	m_keys["Jump"] = new Jump(m_player);
	m_keys["Sprint"] = new Sprint(m_player);
	m_keys["Escape"] = new Escape(m_game);

	m_mouse = new Mouse();
}

void KeyManager::update() {
	double xpos, ypos;
	glfwGetCursorPos(m_window->getGLFWwindow(), &xpos, &ypos);
	m_mouse->handleMovement(xpos, ypos);
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