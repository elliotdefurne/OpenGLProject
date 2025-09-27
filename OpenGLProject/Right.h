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
            m_isPressed = true;
        }
    }

    void onRelease() override {
        if (m_isPressed) {
            m_isPressed = false;
        }
    }

    void ifPressed() override {
        if (m_isPressed) {
            m_player->proccessDirectionKey(direction::RIGHT);
        }
    }
};