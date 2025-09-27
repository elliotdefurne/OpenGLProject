#pragma once

#include "Backward.h"

void Backward::onPress() {
    m_isPressed = true;
}

void Backward::onRelease() {
    m_isPressed = false;
}

void Backward::ifPressed() {
    if (!m_isPressed) return;
    m_player->processDirectionKey(direction::BACKWARD);
}
