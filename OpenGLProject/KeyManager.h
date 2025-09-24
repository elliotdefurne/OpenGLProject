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

    void update();

private:
    std::unordered_map<std::string, Key*> m_keys;
    Player* m_player;
    Game* m_game;

    void loadKeys();
};