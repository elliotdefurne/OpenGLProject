#pragma once
#include "Game.h"
#include "Key.h"


#include "configKeys.h"
#include <GLFW/glfw3.h>


class Escape : public Key {
public:
    Escape(Game* game) : Key(nullptr, "Escape", ConfigKeys::KEY_ESCAPE), m_game(game) {}  // Appel du constructeur parent
    virtual ~Escape() {}

    void onPress() override {
        if (!m_isPressed) {
            m_isPressed = true;
        }
    }

    void onRelease() override {
        if (m_isPressed) {
            delete m_game;
        }
    }

    void ifPressed() override {
		//définit pour éviter les problèmes mais ne fait rien
        if (m_isPressed) {  
        }
    }
private:
	Game* m_game;
};