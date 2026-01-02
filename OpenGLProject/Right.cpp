#include "Right.h"

Right::Right(Player* player) : Key(player, "Right", ConfigKeys::KEY_RIGHT) {
    setIfPressedAction(InputContext::GAME, [this]() {
        m_player->processDirectionKey(EntityRelativeDirection::RIGHT);
    });
}