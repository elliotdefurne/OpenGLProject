#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Right : public Key {
public:
    Right(Player* player) : Key(player, "Right", ConfigKeys::KEY_RIGHT) {}  // Appel du constructeur parent
    virtual ~Right() {}

    void onPress() override {
        if (!m_isPressed) {
            std::cout << "Right onPressed" << std::endl;
            m_isPressed = true;
        }
    }

    void onRelease() override {
        if (m_isPressed) {
            std::cout << "Right onReleased" << std::endl;
            m_isPressed = false;
        }
    }

    void ifPressed() override {
        if (m_isPressed) {
            std::cout << "Right ifPressed" << std::endl;
            m_player->proccessDirectionKey(direction::RIGHT);
        }
    }
};