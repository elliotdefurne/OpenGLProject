#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Jump : public Key {
public:
    Jump(Player* player) : Key(player, "Jump", ConfigKeys::KEY_JUMP) {}  // Appel du constructeur parent
    virtual ~Jump() {}

    void onPress() override {
        if (!m_isPressed) {
            std::cout << "Jump onPressed" << std::endl;
            m_isPressed = true;
        }
    }

    void onRelease() override {
        if (m_isPressed) {
            std::cout << "Jump onReleased" << std::endl;
            m_isPressed = false;
        }
    }

    void ifPressed() override {
        if (m_isPressed) {
            std::cout << "Jump ifPressed" << std::endl;
        }
    }
};