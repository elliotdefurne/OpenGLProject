#include "Escape.h"
#include "Game.h"

Escape::Escape (Game* game) : Key(nullptr, "Escape", ConfigKeys::KEY_ESCAPE), m_game(game) {
    // Action a effectuer lorsque la touche est relachee
    setOnReleaseAction(InputContext::GAME, [this]() {
		m_game->changeState(GameState::STATE_MENU);
    });
    setOnReleaseAction(InputContext::MENU, [this]() {
		m_game->changeState(GameState::STATE_PLAYING);
    });
}