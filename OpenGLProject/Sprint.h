#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Sprint : public Key {
public:
    Sprint(Player* player) : Key(player, "Sprint", ConfigKeys::KEY_SPRINT) {}  // Appel du constructeur parent
    virtual ~Sprint() {}

    void onPress() override {
        if (!m_isPressed) {
            std::cout << "Sprint onPressed" << std::endl;
            m_isPressed = true;
        }
    }

    void onRelease() override {
        if (m_isPressed) {
            std::cout << "Sprint onReleased" << std::endl;
            m_isPressed = false;
        }
    }

    void ifPressed() override {
        if (m_isPressed) {
            std::cout << "Sprint ifPressed" << std::endl;
        }
    }
};