#pragma once
#include <string>
#include "Menu.h"
#include "gamestate.h"

class Game;
class TextRenderer;
class InputManager;

class MenuManager{
    private:
	Game* m_game; // Pointeur vers le jeu principal
    TextRenderer* m_textRenderer;
    Menu m_mainMenu;
    Menu m_pauseMenu;
    Menu m_optionsMenu;
    GameState m_currentState = STATE_MENU;
    GameState m_previousState;

    void initMenus();

    std::string stateToString(GameState state);
public:
    MenuManager(Game* game, TextRenderer* textManager);

    Menu& getCurrentMenu();

    void updateHover(float mouseX, float mouseY);

    void handleClick(float mouseX, float mouseY);

    void draw();

    void changeState(GameState newState);
    GameState getCurrentState() const;
};