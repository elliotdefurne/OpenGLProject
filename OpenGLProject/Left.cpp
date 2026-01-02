#include "Left.h"

// Methode appelee lorsque la touche est appuyee
Left::Left(Player* player) : Key(player, "Left", ConfigKeys::KEY_LEFT) {
    setIfPressedAction(InputContext::GAME, [this]() {
        if (m_player) {
            m_player->processDirectionKey(EntityRelativeDirection::LEFT);
        }
        });

    setIfPressedAction(InputContext::MENU, []() {
        
    });
}