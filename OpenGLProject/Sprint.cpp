#include "Sprint.h"

Sprint::Sprint(Player* player) : Key(player, "Sprint", ConfigKeys::KEY_SPRINT) {
	setOnPressAction(InputContext::GAME, [this]() {
		m_player->setIsSprinting(true);
	});
	setOnReleaseAction(InputContext::GAME, [this]() {
		m_player->setIsSprinting(false);
	});
}