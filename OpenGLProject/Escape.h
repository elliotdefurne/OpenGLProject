#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Escape : public Key {
public:
    Escape(Player* player) : Key(player, "Escape", ConfigKeys::KEY_ESCAPE) {}  // Appel du constructeur parent
    virtual ~Escape() {}

    void onPress() override {
        if (!m_isPressed) {
            std::cout << "Escape onPressed" << std::endl;
            m_isPressed = true;
        }
    }

    void onRelease() override {
        if (m_isPressed) {
            std::cout << "Escape onReleased" << std::endl;
            m_isPressed = false;
        }
    }

    void ifPressed() override {
		//d�finit pour �viter les probl�mes mais ne fait rien
        return ;
    }
};