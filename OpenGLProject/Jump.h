#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Jump : public Key {
public:
    Jump(Player* player) : Key(player, "Jump", ConfigKeys::KEY_JUMP) {}  // Appel du constructeur parent
    virtual ~Jump() {}

    void onPress() override;

    void onRelease() override;

    void ifPressed() override;
};