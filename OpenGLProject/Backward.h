#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Backward : public Key {
public:
    Backward(Player* player) : Key(player, "Backward", ConfigKeys::KEY_BACKWARD) {}
    virtual ~Backward() {}

    void onPress() override {
        if (!m_isPressed) {
            std::cout << "Backward onPressed" << std::endl;
            m_isPressed = true;
        }
    }

    void onRelease() override {
        if (m_isPressed) {
            std::cout << "Backward onReleased" << std::endl;
            m_isPressed = false;
        }
    }

    void ifPressed() override {
        if (m_isPressed) {
            std::cout << "Backward ifPressed" << std::endl;
            m_player->proccessDirectionKey(direction::BACKWARD);
        }
    }
};