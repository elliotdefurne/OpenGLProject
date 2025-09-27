#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Forward : public Key {
public:
    Forward(Player* player) : Key(player, "Forward", ConfigKeys::KEY_FORWARD) {}  // Appel du constructeur parent
    virtual ~Forward() {}

    void onPress() override;

    void onRelease() override;

    void ifPressed() override;
};