#include "MenuManager.h"
#include "TextRenderer.h"
#include "ShaderManager.h"
#include "Game.h"
#include "Rectangle.h"

MenuManager::MenuManager(Game* game, TextRenderer* textRenderer, ShaderManager* shaderManager) : m_game(game), m_textRenderer(textRenderer), m_shaderManager(shaderManager), m_currentState(STATE_MENU), m_previousState(STATE_MENU) {
    initMenus();
}

void MenuManager::initMenus() {
    // Menu principal
    m_mainMenu = Menu(m_textRenderer, "Menu Principal", false);
    m_mainMenu.addItem("Jouer", Constants::WINDOW_WIDTH / 2, 160, 200, 50, [this]() {
        m_game->changeState(STATE_PLAYING);
        });
    m_mainMenu.addItem("Options", Constants::WINDOW_WIDTH / 2, 230, 200, 50, [this]() {
        m_game->changeState(STATE_OPTIONS);
        });
    m_mainMenu.addItem("Quitter", Constants::WINDOW_WIDTH / 2, 300, 200, 50, [this]() {
        m_game->stop();
        });

    Rectangle* rec1 = new Rectangle(m_shaderManager->getShader("rectangle"), 0, 0, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, glm::vec3(1.0f, 0.5f, 0.5f));
    Rectangle* rec2 = new Rectangle(m_shaderManager->getShader("rectangle"), Constants::WINDOW_WIDTH/2, Constants::WINDOW_HEIGHT/2, 20.0f, 20.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Rectangle* rec3 = new Rectangle(m_shaderManager->getShader("rectangle"), 0, 0, 20.0f, 20.0f);
    Rectangle* rec4 = new Rectangle(m_shaderManager->getShader("rectangle"), 0, 0, 20.0f, 20.0f);
	rec2->setRotation(45);
	//rec3->setRotation(45);
    //rec4->setRotation(45);
	m_mainMenu.addShape(0, rec1);
	m_mainMenu.addShape(1, rec2);
	//m_mainMenu.addShape(2, rec3);
	//m_mainMenu.addShape(3, rec4);

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
        printf("Aucun menu a afficher\n");
		return m_mainMenu;
        //throw std::runtime_error("Aucun menu a afficher");
    }
}

void MenuManager::updateHover(double mouseX, double mouseY) {
    getCurrentMenu().updateHover(mouseX, mouseY);
}

void MenuManager::handleClick(double mouseX, double mouseY) {
    getCurrentMenu().handleClick(mouseX, mouseY);
}

void MenuManager::draw() {
    if (m_currentState != STATE_PLAYING) getCurrentMenu().draw();
}

GameState MenuManager::getCurrentState() const {
    return m_currentState;
}