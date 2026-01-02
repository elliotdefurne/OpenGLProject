#pragma once

#include "Jump.h"

Jump::Jump(Player* player) : Key(player, "Jump", ConfigKeys::KEY_JUMP) {
	setIfPressedAction(InputContext::GAME, [this]() {
		m_player->processDirectionKey(EntityRelativeDirection::UP);
	});
}