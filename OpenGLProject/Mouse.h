#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "configKeys.h"



class Mouse {

public:
    Mouse(Player* player) : m_player(player), m_xpos(0.0f), m_ypos(0.0f), m_sensitivity(ConfigKeys::DEFAULT_MOUSE_SENSITIVITY) {}

    void handleMovement(double xpos, double ypos) {
        if ((m_xpos != xpos) or (m_ypos != ypos)) {
            double xoffset = xpos - m_xpos;
            double yoffset = m_ypos - ypos; // Inversé : l'axe Y va de bas en haut
            m_xpos = xpos;
            m_ypos = ypos;
            xoffset *= m_sensitivity;
            yoffset *= m_sensitivity;

            // The angle of rotation up or down is also referred to as pitch;
            // the angle of rotation left or right is also referred to as yaw.
            
			m_player->processMouseMovements(xoffset, yoffset);

        }

    }

private:
    Player* m_player;
    double m_xpos, m_ypos;
    const float m_sensitivity; // Sensibilité de la souris
    glm::highp_vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
};