#include "Escape.h"
#include "Game.h"

void Escape::onPress(InputContext context) {
    if (!m_isPressed) {
        m_isPressed = true;
    }
}

void Escape::onRelease(InputContext context) {
    if (m_isPressed) {
        if (m_game) {
            m_game->stop();
        }
    }
}

void Escape::ifPressed(InputContext context) {
    //definit pour éviter les problèmes mais ne fait rien
    if (m_isPressed) {
    }
}