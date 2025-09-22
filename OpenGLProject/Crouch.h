#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Crouch : public Key {
public:
    Crouch(Player* player) : Key(player, "Crouch", ConfigKeys::KEY_CROUCH) {}  // Appel du constructeur parent
    virtual ~Crouch() {}

    void onPress() override {
        if (!m_isPressed) {
            std::cout << "Crouch onPressed" << std::endl;
            m_isPressed = true;
        }
    }

    void onRelease() override {
        if (m_isPressed) {
            std::cout << "Crouch onReleased" << std::endl;
            m_isPressed = false;
        }
    }

    void ifPressed() override {
        if (m_isPressed) {
            std::cout << "Crouch ifPressed" << std::endl;
            m_player->proccessDirectionKey(direction::DOWN);
        }
    }
};