#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <memory>


#include "Game.h"

#include "Key.h"
#include "Forward.h"
#include "Backward.h"
#include "Left.h"
#include "Right.h"
#include "Crouch.h"
#include "Jump.h"
#include "Sprint.h"
#include "Escape.h"


class KeyManager {
public:
    KeyManager(Game* game, Player* player) : m_game(game), m_player(player) { loadKeys(); }

    ~KeyManager() {
        for (auto& pair : m_keys) {
            delete pair.second;
        }
    }

    Key* getKey(const std::string& name) {
        auto it = m_keys.find(name);
        if (it != m_keys.end()) {
            return it->second;
        }
        throw std::out_of_range("Key not found: " + name);
    }

    void update() {
        for (const auto& pair : m_keys) {
            Key* key = pair.second;
            int state = glfwGetKey(glfwGetCurrentContext(), key->getKey());
			bool wasPressed = key->getStatus();

            key->ifPressed();
            if (state == GLFW_PRESS) {
                key->onPress();
            } else if (state == GLFW_RELEASE) {
                key->onRelease();
            }
        }
	}

private:
    std::unordered_map<std::string, Key*> m_keys;
    Player* m_player;
    Game* m_game;

    void loadKeys() {
        m_keys["Forward"] = new Forward(m_player);
        m_keys["Backward"] = new Backward(m_player);
        m_keys["Left"] = new Left(m_player);
        m_keys["Right"] = new Right(m_player);
        m_keys["Crouch"] = new Crouch(m_player);
        m_keys["Jump"] = new Jump(m_player);
		m_keys["Sprint"] = new Sprint(m_player);
		m_keys["Escape"] = new Escape(m_game);
    }
};