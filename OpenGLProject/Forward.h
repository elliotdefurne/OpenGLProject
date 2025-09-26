#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Forward : public Key {
public:
    Forward(Player* player) : Key(player, "Forward", ConfigKeys::KEY_FORWARD) {}  // Appel du constructeur parent
    virtual ~Forward() {}

    void onPress() override {
        if (!m_isPressed) {
            std::cout << "Forward onPressed" << std::endl;
		    m_isPressed = true;
        }
    }

    void onRelease() override {
        if (m_isPressed) {
            std::cout << "Forward onReleased" << std::endl;
            m_isPressed = false;
        }
    }

    void ifPressed() override {
        if (m_isPressed) {
            std::cout << "Forward ifPressed" << std::endl;
            m_player->proccessDirectionKey(direction::FORWARD);
        }
    }
};