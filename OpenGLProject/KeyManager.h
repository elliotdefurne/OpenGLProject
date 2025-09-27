#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <memory>

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
#include "Window.h"

class Game; // Declaration anticipee de la classe Game & on include Game.h dans KeyManager.cpp

class KeyManager {
public:
    KeyManager(Game* game, Window* window, Player* player) : m_game(game), m_window(window), m_player(player) { loadKeys(); }

    ~KeyManager() { for (auto& pair : m_keys) { delete pair.second; } }

    Key* getKey(const std::string& name);

    void update();

private:
    std::unordered_map<std::string, Key*> m_keys;
	Mouse* m_mouse;
    
    Player* m_player;
    Game* m_game;
    Window* m_window;

    void loadKeys();
};