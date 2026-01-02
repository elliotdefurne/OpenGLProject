#pragma once

#include "Crouch.h"

Crouch::Crouch(Player* player) : Key(player, "Crouch", ConfigKeys::KEY_CROUCH) {
	// Action a effectuer lorsque la touche est appuyee
	setIfPressedAction(InputContext::GAME, [this]() {
		if (m_player) {
			m_player->processDirectionKey(EntityRelativeDirection::DOWN);
		}
	});
}