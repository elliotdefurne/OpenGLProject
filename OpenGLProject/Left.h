#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Left : public Key {
public:
    Left(Player* player) : Key(player, "Left", ConfigKeys::KEY_LEFT) {}  // Appel du constructeur parent
    virtual ~Left() {}

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
            m_player->proccessDirectionKey(direction::LEFT);
        }
    }
};