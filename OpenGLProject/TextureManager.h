#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>

#include "Texture.h"
#include "constants.h"

class TextureManager {

	public:
		TextureManager() { loadTextures(); };
		~TextureManager() = default;
	
		Texture* getTexture(const int index) {
			if (0 <= index && index<m_textures.size()) {
				return m_textures.at(index);
			}
			else {
				throw std::out_of_range("Texture index out of range");
			}
		}

	private:
		void loadTextures(std::string texturesFolderPath = Constants::TEXTURES_FOLDER_PATH) {
			bool folderExists = std::filesystem::is_directory(texturesFolderPath);
			if (!folderExists) {
				std::cerr << "Textures folder path does not exist: " << texturesFolderPath << std::endl;
				return;
			}
			for (const auto& entry : std::filesystem::directory_iterator(texturesFolderPath)) {
				const int stringLenght = entry.path().string().size();
				if (entry.is_regular_file() && entry.path().string().substr(stringLenght - 4) == ".png") {
					std::string filePath = entry.path().string();
					int textureID = static_cast<int>(m_textures.size());
					Texture* texture = new Texture(filePath, textureID);
					m_textures.emplace_back(texture);
				}
			}
		}

		std::vector<Texture*> m_textures;
};