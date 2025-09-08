#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.h"

/**
 * @brief Constructeur de la classe Texture.
 *
 * Initialise l'objet texture avec un chemin de fichier et charge la texture en mémoire GPU.
 *
 * @param filePath Chemin vers le fichier image à charger.
 */
Texture::Texture(const std::string& filePath, const int textureID) : m_filePath(filePath), m_textureID(textureID) {
	loadTexture();
}

/**
 * @brief Destructeur de la classe Texture.
 *
 * Libère la mémoire GPU associée à la texture.
 */
Texture::~Texture() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &m_textureID);
}

/**
 * @brief Charge la texture depuis un fichier image.
 *
 * Utilise stb_image pour lire les pixels, crée une texture OpenGL,
 * définit ses paramètres (wrap, filtre), et génère les mipmaps.
 *
 * En cas d'échec du chargement, un message d'erreur est affiché sur stderr.
 */
void Texture::loadTexture() {
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image using stb_image
	stbi_set_flip_vertically_on_load(true); // Flip the image vertically
	bool filepathExists = std::filesystem::exists(m_filePath);
	if (!filepathExists) {
		std::cerr << "File path does not exist: " << m_filePath << std::endl;
		return;
	}

	unsigned char* data = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_nrChannels, 4);
	if (data) {
		m_nrChannels = 4;
		GLenum format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cerr << "Failed to load texture: " << m_filePath << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}