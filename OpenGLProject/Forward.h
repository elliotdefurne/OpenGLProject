#pragma once
#include "Key.h"
#include <GLFW/glfw3.h>

class Forward : public Key {
public:
    Forward() : Key("Forward", GLFW_KEY_Z) {}  // Appel du constructeur parent
    virtual ~Forward() {}

    void onPress() const override {
        std::cout << "Forward pressed" << std::endl;
    }

    void onRelease() const override {
        std::cout << "Forward released" << std::endl;
    }
};