#include "Escape.h"
#include "Game.h"

void Escape::onPress() {
    if (!m_isPressed) {
        m_isPressed = true;
    }
}

void Escape::onRelease() {
    if (m_isPressed) {
        if (m_game) {
            m_game->stop();
        }
    }
}

void Escape::ifPressed() {
    //definit pour éviter les problèmes mais ne fait rien
    if (m_isPressed) {
    }
}