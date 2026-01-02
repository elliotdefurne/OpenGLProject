#pragma once
#include <glad/glad.h>
#include <string>
#include <map>

class ShaderManager; // Déclaration anticipée

struct Character {
    unsigned int textureID;
    int sizeX, sizeY;
    int bearingX, bearingY;
    unsigned int advance;
};

class TextRenderer {
private:
    ShaderManager* m_shaderManager;
    std::map<char, Character> m_characters;
    unsigned int m_VAO, m_VBO;
    unsigned int m_shaderProgram;
    float m_fontSize;
    int m_screenWidth, m_screenHeight;

public:
    TextRenderer(ShaderManager* shaderManager);
    ~TextRenderer();

    void setScreenSize(int width, int height);
    bool loadFont(const std::string& fontPath, float fontSize);
    void renderText(const std::string& text, float x, float y, float scale,
        float r, float g, float b);
    float getTextWidth(const std::string& text, float scale);
};