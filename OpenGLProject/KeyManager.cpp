#pragma once
#include "KeyManager.h"
#include "Key.h"
#include "Forward.h"
#include "Backward.h"
#include "Left.h"
#include "Right.h"
#include "Crouch.h"
#include "Jump.h"
#include "Sprint.h"
#include "Escape.h"
#include "Mouse.h"
#include "Flashlight.h"

#include "Window.h"

KeyManager::~KeyManager() { for (auto& pair : m_keys) { delete pair.second; } }

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
	m_keys["Flashlight"] = new Flashlight(m_player);
	m_keys["Escape"] = new Escape(m_game);

	m_mouse = new Mouse(m_player);
}

void KeyManager::update() {
	double xpos, ypos;
	glfwGetCursorPos(m_window->getGLFWwindow(), &xpos, &ypos);
	m_mouse->handleMovement(xpos, ypos); // Appel avec des valeurs factices pour l'instant
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