#pragma once
#include <string>
#include "Menu.h"

class Game;
class TextRenderer;
class InputManager;

// Énumération des états du jeu
enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_OPTIONS
};

class MenuManager{
    private:
	Game* m_game; // Pointeur vers le jeu principal
    TextRenderer* m_textRenderer;
    InputManager* m_inputManager;
    Menu mainMenu;
    Menu pauseMenu;
    Menu optionsMenu;
    GameState currentState = STATE_PLAYING;
    GameState previousState;

    void initMenus();

    void changeState(GameState newState);

    std::string stateToString(GameState state);
public:
    MenuManager(Game* game, TextRenderer* textManager, InputManager* inputManager);

    Menu& getCurrentMenu();

    void updateHover(float mouseX, float mouseY);

    void handleClick(float mouseX, float mouseY);

    void draw();

    GameState getCurrentState() const;
};