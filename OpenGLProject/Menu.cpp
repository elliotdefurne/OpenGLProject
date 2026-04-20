#include "Menu.h"
#include "TextRenderer.h"

void Menu::drawTextCentered(const std::string& text, float centerX, float centerY, glm::vec3 color) {
    float textWidth = m_textRenderer->getTextWidth(text, 1.0f);
    float textHeight = m_textRenderer->getTextHeight(text, 1.0f); // Ajoutez cette méthode si elle n'existe pas
    
    float startX = centerX - textWidth / 2.0f;
    float startY = centerY; // Centrage vertical basé sur la hauteur réelle
    
    m_textRenderer->renderText(text, startX, startY, 1.0f, color.r, color.g, color.b);
}

void Menu::draw() {
    for (auto& shape : m_shapes) {
        shape.second->draw();
    }

    // Dessiner le titre si présent
    if (!m_title.empty()) {
        drawTextCentered(m_title, m_titleX, m_titleY);
    }

    // Dessiner les items du menu
    for (const auto& item : m_items) {
               
        // Texte centré
        float centerX = item.x + item.width / 2.0f;
        float centerY = item.y + item.height / 2.0f;

        if (item.isHovered) {
            drawTextCentered(item.text, centerX, centerY, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else {
            drawTextCentered(item.text, centerX, centerY);

        }
    }
}