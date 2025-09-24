#pragma once

#include "Key.h"
#include "configKeys.h"
#include <GLFW/glfw3.h>

class Backward : public Key {
public:
    Backward(Player* player) : Key(player, "Backward", ConfigKeys::KEY_BACKWARD) {}
	virtual ~Backward() {}

    void onPress() override;
    void onRelease() override;
    void ifPressed() override;
};
