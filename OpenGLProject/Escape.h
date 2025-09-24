#pragma once
#include "Key.h"


#include "configKeys.h"
#include <GLFW/glfw3.h>

class Game; // Déclaration anticipée de la classe Game & on include Game.h dans Escape.cpp

class Escape : public Key {
public:
    Escape(Game* game) : Key(nullptr, "Escape", ConfigKeys::KEY_ESCAPE), m_game(game) {};  // Appel du constructeur parent
    virtual ~Escape() {}

    void onPress() override;
    void onRelease() override;
    void ifPressed() override;
private:
	Game* m_game;
};