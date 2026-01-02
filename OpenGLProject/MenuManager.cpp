#include "MenuManager.h"
#include "TextRenderer.h"
#include "Game.h"
#include "InputManager.h"

MenuManager::MenuManager(Game* game, TextRenderer* textRenderer, InputManager* inputManager) : m_game(game), m_textRenderer(textRenderer), m_inputManager(inputManager),  currentState(STATE_MENU), previousState(STATE_MENU) {
    initMenus();
}

void MenuManager::initMenus() {
    // Menu principal
    mainMenu = Menu(m_textRenderer, "Menu Principal", false);
    mainMenu.addItem("Jouer", 200, 160, 200, 50, [this]() {
        changeState(STATE_PLAYING);
        });
    mainMenu.addItem("Options", 200, 230, 200, 50, [this]() {
        changeState(STATE_OPTIONS);
        });
    mainMenu.addItem("Quitter", 200, 300, 200, 50, [this]() {
        m_game->stop();
        });

    // Menu pause (avec overlay)
    pauseMenu = Menu(m_textRenderer, "Pause", true);
    pauseMenu.addItem("Reprendre", 200, 300, 200, 50, [this]() {
        changeState(STATE_PLAYING);
        });
    pauseMenu.addItem("Menu Principal", 200, 230, 200, 50, [this]() {
        changeState(STATE_MENU);
        });
    pauseMenu.addItem("Quitter", 200, 160, 200, 50, [this]() {
        m_game->stop();
        });

    // Menu options
    optionsMenu = Menu(m_textRenderer, "Options", false);
    optionsMenu.addItem("Son: ON", 200, 300, 200, 50, [this]() {
        std::cout << "Toggle son" << std::endl;
        });
    optionsMenu.addItem("Retour", 200, 230, 200, 50, [this]() {
        changeState(previousState == STATE_PLAYING ? STATE_PAUSED : STATE_MENU);
        });
}

void MenuManager::changeState(GameState newState) {
    previousState = currentState;
    currentState = newState;
    switch (newState) {
    case STATE_MENU:
    case STATE_OPTIONS:
        m_inputManager->setContext(InputContext::MENU);
        break;
    case STATE_PLAYING:
        m_inputManager->setContext(InputContext::GAME);
        break;
    case STATE_PAUSED:
        m_inputManager->setContext(InputContext::PAUSED);
        break;
    }
    std::cout << "État: " << stateToString(newState) << std::endl;
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
    switch (currentState) {
    case STATE_MENU:
        return mainMenu;
    case STATE_PAUSED:
        return pauseMenu;
    case STATE_OPTIONS:
        return optionsMenu;
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
    getCurrentMenu().draw();
}

GameState MenuManager::getCurrentState() const {
    return currentState;
}