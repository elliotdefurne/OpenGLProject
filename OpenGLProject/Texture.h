#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>

class Texture {
	public:
	Texture(const std::string& filePath, const int textureID);
	~Texture();
	
	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
	inline int getBPP() const { return m_BPP; }
	inline GLuint getID() const { return m_textureID; }
private:
	void loadTexture();
	
	const std::string& m_filePath;

	GLuint m_textureID;
	int m_width, m_height, m_nrChannels, m_BPP; // Bits Per Pixel 
};