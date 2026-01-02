#include <glad/glad.h>

#include "Menu.h"
#include "InputManager.h"
#include "TextRenderer.h"

void Menu::drawRect(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void Menu::drawOverlay() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(600, 0);
    glVertex2f(600, 500);
    glVertex2f(0, 500);
    glEnd();
    glDisable(GL_BLEND);
}


void Menu::drawText(const std::string& text, float x, float y) {
    
}

void Menu::drawTextCentered(const std::string& text, float centerX, float centerY) {
    int textWidth = m_textRenderer->getTextWidth(text, 1.0f);
    float startX = centerX - textWidth / 2.0f;
    float startY = centerY - 4; // Ajustement vertical pour centrer
	m_textRenderer->renderText(text, startX, startY, 1.0f, 1.0f, 1.0f, 1.0f);
}


void Menu::draw() {
    if (m_drawBackground) {
        drawOverlay();
    }

    // Dessiner le titre si présent
    if (!m_title.empty()) {
        drawRect(m_titleX, m_titleY, m_titleWidth, m_titleHeight, 0.2f, 0.3f, 0.5f);
        float titleCenterX = m_titleX + m_titleWidth / 2.0f;
        float titleCenterY = m_titleY + m_titleHeight / 2.0f;
        drawTextCentered(m_title, titleCenterX, titleCenterY);
    }

    // Dessiner les items du menu
    for (const auto& item : m_items) {
        // Fond du bouton
        if (item.isHovered) {
            drawRect(item.x, item.y, item.width, item.height, 0.3f, 0.5f, 0.7f);
        }
        else {
            drawRect(item.x, item.y, item.width, item.height, 0.15f, 0.25f, 0.35f);
        }

        // Bordure
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(item.x, item.y);
        glVertex2f(item.x + item.width, item.y);
        glVertex2f(item.x + item.width, item.y + item.height);
        glVertex2f(item.x, item.y + item.height);
        glEnd();

        // Texte centré
        float centerX = item.x + item.width / 2.0f;
        float centerY = item.y + item.height / 2.0f;
        drawTextCentered(item.text, centerX, centerY);
    }
}