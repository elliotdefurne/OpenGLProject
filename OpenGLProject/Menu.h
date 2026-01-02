#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <glm/glm.hpp>

#include "constants.h"

class InputManager; // Déclaration anticipée
class TextRenderer; // Déclaration anticipée

// Structure pour un élément de menu
struct MenuItem {
    std::string text;
    float x, y, width, height;
    bool isHovered;
    std::function<void()> callback;

    MenuItem(const std::string& t, float px, float py, float w, float h, std::function<void()> cb)
        : text(t), x(px), y(py), width(w), height(h), isHovered(false), callback(cb) {
    }

    bool contains(float px, float py) const {
        return (px >= x && px <= x + width && py >= y && py <= y + height);
    }
};

// Classe Menu
class Menu {
private:
    TextRenderer* m_textRenderer;
    std::vector<MenuItem> m_items;
    std::string m_title;
    float m_titleX, m_titleY, m_titleWidth, m_titleHeight;
    bool m_drawBackground;

    void drawRect(float x, float y, float width, float height, float r, float g, float b);
    void drawOverlay();
    void drawTextCentered(const std::string& text, float centerX, float centerY, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

public:
    Menu(TextRenderer* textRenderer = nullptr, const std::string& t = "", bool bg = true)
        : m_textRenderer(textRenderer), m_title(t), m_titleX(Constants::MENU_TITLE_X), m_titleY(Constants::MENU_TITLE_Y), m_titleWidth(Constants::MENU_TITLE_W), m_titleHeight(Constants::MENU_TITLE_H), m_drawBackground(bg) {
    }

    void addItem(const std::string& text, float x, float y, float width, float height, std::function<void()> callback) {
        m_items.emplace_back(text, x, y, width, height, callback);
    }

    void clear() {
        m_items.clear();
    }

    std::vector<MenuItem> getItems() { return m_items; }
    void setSelectedItem(int index) { 
        for (auto& item : m_items) {
            item.isHovered = false;
		}
        m_items[index].isHovered = true;
    }

    void updateHover(float mouseX, float mouseY) {
        for (auto& item : m_items) {
            item.isHovered = false;
        }
        for (auto& item : m_items) {
            item.isHovered = item.contains(mouseX, mouseY);
        }
    }

    bool handleClick(float mouseX, float mouseY) {
        printf("mouseX = %f ; mouseY = %f\n", mouseX, mouseY);
        for (auto& item : m_items) {
            if (item.contains(mouseX, mouseY) && item.callback) {
                item.callback();
                return true;
            }
        }
        return false;
    }

    void update(InputManager* inputManager) {
        // Logique de mise à jour du menu si nécessaire
	    
    }

    void draw();
};