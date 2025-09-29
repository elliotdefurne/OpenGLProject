#pragma once

#include "Cube.h"

class LightBlock : public Cube{
public:
	LightBlock(glm::vec3 center, float edge, Shader* shader, Texture* texture);
	~LightBlock();

	void draw() override;
};

