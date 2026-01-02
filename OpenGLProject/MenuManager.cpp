#include "MenuManager.h"
#include "TextRenderer.h"
#include "Game.h"

MenuManager::MenuManager(Game* game, TextRenderer* textRenderer) : m_game(game), m_textRenderer(textRenderer), m_currentState(STATE_MENU), m_previousState(STATE_MENU) {
    initMenus();
}

void MenuManager::initMenus() {
    // Menu principal
    m_mainMenu = Menu(m_textRenderer, "Menu Principal", false);
    m_mainMenu.addItem("Jouer", 200, 160, 200, 50, [this]() {
        m_game->changeState(STATE_PLAYING);
        });
    m_mainMenu.addItem("Options", 200, 230, 200, 50, [this]() {
        m_game->changeState(STATE_OPTIONS);
        });
    m_mainMenu.addItem("Quitter", 200, 300, 200, 50, [this]() {
        m_game->stop();
        puts("test");
        });

    // Menu pause (avec overlay)
    m_pauseMenu = Menu(m_textRenderer, "Pause", true);
    m_pauseMenu.addItem("Reprendre", 200, 300, 200, 50, [this]() {
        m_game->changeState(STATE_PLAYING);
        });
    m_pauseMenu.addItem("Menu Principal", 200, 230, 200, 50, [this]() {
        m_game->changeState(STATE_MENU);
        });
    m_pauseMenu.addItem("Quitter", 200, 160, 200, 50, [this]() {
        m_game->stop();
        });

    // Menu options
    m_optionsMenu = Menu(m_textRenderer, "Options", false);
    m_optionsMenu.addItem("Son: ON", 200, 300, 200, 50, [this]() {
        std::cout << "Toggle son" << std::endl;
        });
    m_optionsMenu.addItem("Retour", 200, 230, 200, 50, [this]() {
        m_game->changeState(m_previousState == STATE_PLAYING ? STATE_PAUSED : STATE_MENU);
        });
}

void MenuManager::changeState(GameState newState) {
    m_previousState = m_currentState;
    m_currentState = newState;
}

std::string MenuManager::stateToString(GameState state) {
    switch (state) {
    case STATE_MENU: return "Menu";
    case STATE_PLAYING: return "Jeu";
    case STATE_PAUSED: return "Pause";
    case STATE_OPTIONS: return "Options";
    default: return "Inconnu";
    }
}



Menu& MenuManager::getCurrentMenu() {
    switch (m_currentState) {
    case STATE_MENU:
        return m_mainMenu;
    case STATE_PAUSED:
        return m_pauseMenu;
    case STATE_OPTIONS:
        return m_optionsMenu;
    default:
        throw std::runtime_error("Aucun menu à afficher");
    }
}

void MenuManager::updateHover(float mouseX, float mouseY) {
    getCurrentMenu().updateHover(mouseX, mouseY);
}

void MenuManager::handleClick(float mouseX, float mouseY) {
    getCurrentMenu().handleClick(mouseX, mouseY);
}

void MenuManager::draw() {
    if (m_currentState != STATE_PLAYING) getCurrentMenu().draw();
}

GameState MenuManager::getCurrentState() const {
    return m_currentState;
}