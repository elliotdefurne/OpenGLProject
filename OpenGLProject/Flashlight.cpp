#pragma once

#include "Flashlight.h"

Flashlight::Flashlight(Player* player) : Key(player, "Flashlight", ConfigKeys::KEY_FLASHLIGHT) {
	setOnReleaseAction(InputContext::GAME, [this]() {
		m_player->processFlashLightKey();
	});
}