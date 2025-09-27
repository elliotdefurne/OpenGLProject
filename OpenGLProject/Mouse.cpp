#include "Mouse.h"
#include "Player.h"

void Mouse::handleMovement(double xpos, double ypos) {
    if ((m_xpos != xpos) or (m_ypos != ypos)) {
        double xoffset = xpos - m_xpos;
        double yoffset = m_ypos - ypos; // Inverse : l'axe Y va de bas en haut
        m_xpos = xpos;
        m_ypos = ypos;
        xoffset *= m_sensitivity;
        yoffset *= m_sensitivity;

        // The angle of rotation up or down is also referred to as pitch;
        // the angle of rotation left or right is also referred to as yaw.

        m_player->processMouseMovements(xoffset, yoffset);

    }
}