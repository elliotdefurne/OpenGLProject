#pragma once

class ShaderManager;

class ShapeRenderer {
public:
	ShapeRenderer(ShaderManager* shaderManager);

	~ShapeRenderer() = default;

	void drawRectangle(float x = 0.0f, float y = 0.0f, float width = 1.0f, float height = 1.0f);
private:
	ShaderManager* m_shaderManager;
};