#include "Right.h"

void Right::onPress() {
    if (!m_isPressed) {
        m_isPressed = true; // Indique que la touche est maintenue
    }
}


void Right::onRelease() {
    if (m_isPressed) {
        m_isPressed = false; // Indique que la touche n'est plus maintenue
    }
}

void Right::ifPressed() {
    if (m_isPressed) {
        m_player->processDirectionKey(direction::RIGHT);
        // Demande au joueur de se deplacer a droite
    }
}