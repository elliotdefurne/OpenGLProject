#include "Sprint.h"

void Sprint::onPress() {
    if (!m_isPressed) {
        m_isPressed = true; // Indique que la touche est maintenue
        // Ici, on pourrait modifier la vitesse du joueur pour sprinter
    }
}

void Sprint::onRelease() {
    if (m_isPressed) {
        m_isPressed = false; // Indique que la touche n'est plus maintenue
        // Ici, on pourrait remettre la vitesse normale du joueur
    }
}

void Sprint::ifPressed() {
    if (m_isPressed) {
        // Action continue si necessaire pendant le sprint
        // Par exemple, maintenir la vitesse sprint ou jouer une animation
    }
}