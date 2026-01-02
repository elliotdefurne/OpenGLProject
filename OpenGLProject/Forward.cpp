#pragma once

#include "Forward.h"

Forward::Forward(Player* player) : Key(player, "Forward", ConfigKeys::KEY_FORWARD) {
	setIfPressedAction(InputContext::GAME, [this]() {
		m_player->processDirectionKey(EntityRelativeDirection::FORWARD);
	}); 
}