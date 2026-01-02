#pragma once

#include "Backward.h"

Backward::Backward(Player* player) : Key(player, "Backward", ConfigKeys::KEY_BACKWARD) {
    setIfPressedAction(InputContext::GAME, [this]() {
        if (m_player) {
            m_player->processDirectionKey(EntityRelativeDirection::BACKWARD);
        }
        });

    setIfPressedAction(InputContext::MENU, [this]() {
      
    });
}
