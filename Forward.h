#pragma once

#include "Key.h"
#include <GLFW/glfw3.h>

class Forward : public Key {
	public:
		Forward() : Key() {}
		virtual ~Forward() {}
		void onPress() const override {
			std::cout << "Forward pressed" << std::endl;
		}
		void onRelease() const override {
			std::cout << "Forward released" << std::endl;
		}
	private:
		const std::string m_name = "Forward";
		const int m_key = GLFW_KEY_Z;
};