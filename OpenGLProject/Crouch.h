#pragma once
#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Crouch : public Key {
public:
    Crouch(Player* player) : Key(player, "Crouch", ConfigKeys::KEY_CROUCH) {}  // Appel du constructeur parent
    virtual ~Crouch() {}

    void onPress() override;

    void onRelease() override;

    void ifPressed() override;
};