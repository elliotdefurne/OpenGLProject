#include "Left.h"

// Methode appelee lorsque la touche est appuyee
void Left::onPress(InputContext context) {
    if (!m_isPressed) {
        m_isPressed = true; // Change l'etat pour indiquer que la touche est appuyee

    }
}

// Methode appelee lorsque la touche est relachee
void Left::onRelease(InputContext context) {
    if (m_isPressed) {
        m_isPressed = false; // Change l'etat pour indiquer que la touche est relachee
    }
}

// Methode appelee chaque frame si la touche est maintenue
void Left::ifPressed(InputContext context) {
    if (m_isPressed) {
        m_player->processDirectionKey(direction::LEFT);
        // Demande au joueur de se deplacer a gauche
        // "processDirectionKey" est la methode du joueur qui gere le deplacement
    }
}