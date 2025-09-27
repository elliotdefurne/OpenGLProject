#pragma once
#include <GLFW/glfw3.h>

namespace ConfigKeys {
	inline const int KEY_FORWARD = GLFW_KEY_W;
	inline const int KEY_BACKWARD = GLFW_KEY_S;
	inline const int KEY_LEFT = GLFW_KEY_A;
	inline const int KEY_RIGHT = GLFW_KEY_D;
	inline const int KEY_CROUCH = GLFW_KEY_LEFT_CONTROL;
	inline const int KEY_JUMP = GLFW_KEY_SPACE;
	inline const int KEY_SPRINT = GLFW_KEY_LEFT_SHIFT;
	inline const int KEY_ESCAPE = GLFW_KEY_ESCAPE;

	inline const float DEFAULT_MOUSE_SENSITIVITY = 0.1f;
	// Add other key names here as needed
}