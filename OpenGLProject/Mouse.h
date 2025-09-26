#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <memory>

#include "configKeys.h"



class Mouse {

public:

    void handleMovement(double xpos, double ypos) {

        if ((m_oldxpos!=xpos) or (m_oldypos!=ypos)) {
            double xoffset = xpos - m_oldxpos;
            double yoffset = m_oldypos - ypos; // Inversé : l'axe Y va de bas en haut
            m_oldxpos = xpos;
            m_oldypos = ypos;
            xoffset *= m_sensitivity;
            yoffset *= m_sensitivity;
            // Mettre à jour les angles de la caméra ici (non implémenté dans cette classe)
            // Par exemple : cameraYaw += xoffset; cameraPitch += yoffset;

            double cameraYaw;
            double cameraPitch;


            std::cout << "Mouse Position: ("
                << xoffset << ", "
                << yoffset << ")\n";

		}

    }

private:
    double m_oldxpos = 0.0;
    double m_oldypos = 0.0;
	const float m_sensitivity = ConfigKeys::sensitivity; // Sensibilité de la souris
};